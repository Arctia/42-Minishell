#include "executor.h"

/*
	***********************************************************
					ft_execvepipe
	***********************************************************
*/
void	ft_execvepipe(t_command *cmd)
{
	char	*path;
	char	**arg;
	int		status;
	pid_t	pid;

	path = ft_findpath(cmd, 0);
	arg = ft_listtomatrix(cmd);
	if ((pid = fork()) < 0)
		perror("execv fork failed");
	if (!pid)
	{
		if (execve(path, arg, cmd->shell->env) == -1)
		{
			perror("execv execution failed");
			free_shell(cmd->shell);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
}
/*
	***********************************************************
					ft_pipe
	***********************************************************
	no pid array
	mancano ft_expander, ft_redir(ancora da scrivere)
	cat | ls non funziona come bash

*/

void	ft_pipe(t_command *cmd)
{
	int		status;
	int		std_cpy[2];
	int		fd[2];
	int		pid;

	std_cpy[0] = dup(0);	// input
	std_cpy[1] = dup(1);	//	output
	while (cmd && (cmd->spc[PIPE] || cmd->prev->spc[PIPE]))
	{
		pipe(fd);
		if((pid=fork())==0)
		{
			close(fd[0]);
			if (cmd->spc[PIPE])
				dup2(fd[1], STDOUT_FILENO);
			else
				dup2(std_cpy[1], STDOUT_FILENO);
			close(std_cpy[1]);
			close(fd[1]);
			ft_execvepipe(cmd);
			exit(1);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid, &status, WUNTRACED);
		cmd = cmd->next;
	}
	dup2(std_cpy[0], STDIN_FILENO);
	close(std_cpy[0]);
	close(std_cpy[1]);
}

/*
	***********************************************************
					ft_pipeline
	***********************************************************
	unused with pid array
	mancano ft_expander, ft_redir(ancora da scrivere)

*/

void	ft_pipeline(t_command *cmd)
{
	int		status;
	int		std_cpy[2];
	int		fd[2];
	pid_t	*pid;
	int		n_pipe = cmd->shell->mc_pipes;
	int		i=0;

	std_cpy[0] = dup(0);	// input
	std_cpy[1] = dup(1);	//	output
	pid = malloc(sizeof(int) * n_pipe);
	while (cmd && (cmd->spc[PIPE] || cmd->prev->spc[PIPE]))
	{
		pipe(fd);
		if((pid[i]=fork())==0)
		{
			close(fd[0]);
			if (cmd->spc[PIPE])
				dup2(fd[1], STDOUT_FILENO);
			else
				dup2(std_cpy[1], STDOUT_FILENO);
			close(fd[1]);
			ft_execvepipe(cmd);
		}
		else
		{
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			// free_shell(cmd->shell);
		}
		i++;	
		cmd = cmd->next;
	}
	dup2(std_cpy[0], STDIN_FILENO);
	close(std_cpy[0]);
	close(std_cpy[1]);
	i = -1;
	while (++i < n_pipe)
		waitpid(pid[i],&status,0);
	free(pid);
}