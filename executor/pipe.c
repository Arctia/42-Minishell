#include "executor.h"

// typedef int	Pipe[2];

/*
	***********************************************************
					ft_execvepipe
	***********************************************************
	different ft_execv without fork i don't know if needed
*/

// void ft_pipe(t_command *cmd)
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	int		tmp_fd = dup(STDIN_FILENO);
// 	// int		n_pipes = cmd->shell->mc_pipes+1;
// 	if (cmd->spc[PIPE])
// 	{

// 		pipe(fd);
// 		if ((pid = fork()) == 0)
// 		{
// 			close(fd[0]);
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[1]);
// 			ft_execvepipe(cmd,tmp_fd);
// 		}
// 		else
// 		{
// 			close(fd[1]);
// 			close(tmp_fd);
// 			tmp_fd = fd[0];
// 		}
// 	}
// }

// void ft_execvepipe(t_command *cmd, int tmp_fd)
// {
// 	char	*path;
// 	char	**arg;

// 	arg = ft_listtomatrix(cmd);

// 	path = ft_findpath(cmd, 0);

// 	dup2(tmp_fd, STDIN_FILENO);
// 	close(tmp_fd);
// 	if (execve(path, arg, cmd->shell->env) == -1)
// 		perror("execution failed");
// }

// void	ft_execvepipe(t_command *cmd)
// {
// 	char	*path;
// 	char	**arg;
// 	int		status;
// 	pid_t	pid;

// 	path = ft_findpath(cmd, 0);
// 	arg = ft_listtomatrix(cmd);
// 	pid = fork();
// 	if (!pid)
// 	{
// 		if (execve(path, arg, cmd->shell->env) == -1)
// 		{
// 			perror("execv execution failed");
// 			free_shell(cmd->shell);
// 			exit(1);
// 		}
// 	}
// 	else if (pid < 0)
// 		perror("execv fork failed");
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		// while (!WIFEXITED(status) && !WIFSIGNALED(status))
// 		// 	waitpid(pid, &status, WUNTRACED);
// 	}
// 	// exit(EXIT_FAILURE);
// }

// void	ft_pipejunior(t_command *cmd, int *fd, int n_pipe, int std_cpy)
// {
// 	close(fd[0]);
// 	if (n_pipe == cmd->shell->mc_pipes)
// 		dup2(std_cpy, 1);
// 	else
// 		dup2(fd[1], 1);
// 	close(fd[1]);
// 	ft_execvepipe(cmd);
// }

// void	ft_pipeline(t_command *cmd, int std_cpy)
// {
// 	int		fd[2];
// 	pid_t	pid;
// 	int		n_pipe;
// 	int		i = 0;

// 	n_pipe = cmd->shell->mc_pipes;
// 	while (i < n_pipe)
// 	{
// 		if (pipe(fd) != 0)
// 			perror("filed to create fd");
// 		if ((pid = fork()) < 0)
// 			perror("failed to fork");
// 		if (!pid)
// 		{
// 			ft_pipejunior(cmd, &fd[2], i, std_cpy);
// 		}
// 		else
// 		{
// 			dup2(fd[0],0);
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		i++;
// 	}
// }

// void	ft_pipe(t_command *cmd)
// {
// 	int		status;
// 	int 	std_cpy[2];

// 	std_cpy[0] = dup(0);
// 	std_cpy[1] = dup(1);
// 	ft_pipeline(cmd, std_cpy[1]);
// 	while ((waitpid(-1, &status, 0)))
// 		;
// 	dup2(std_cpy[0], 0);
// }



















void	ft_execvepipe(t_command *cmd)
{
	char	*path;
	char	**arg;
	int		status;
	pid_t	pid;

	// (void) pid;

	path = ft_findpath(cmd, 0);
	arg = ft_listtomatrix(cmd);
	
	if ((pid = fork()) < 0)
		perror("execv fork failed");
	if (!pid)
	{
		if (execve(path, arg, cmd->shell->env) == -1)
		{
			perror("execv execution failed");
			// free_shell(cmd->shell);
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
void	ft_pipe(t_command *cmd)
{
	int		status;
	int		std_cpy[2];
	int		fd[2];
	int		pid;

	std_cpy[0] = dup(0);
	std_cpy[1] = dup(1);
	if (cmd->shell->mc_pipes == 1)
	{
		pipe(fd);
		if((pid=fork())==0)
		{
			close(fd[0]);
			// ft_printf("singlelast pipe print sti on stdout");
			dup2(fd[1], STDOUT_FILENO);
			ft_execvepipe(cmd);
		}
		close(fd[1]);
		ft_execvepipe(cmd->next);
		exit(0);
	}
	waitpid(pid,&status,0);
	if (cmd->shell->mc_pipes>1)
		ft_pipeline(cmd);
}

void	ft_pipeline(t_command *cmd)
{
	int		status;
	int		std_cpy[2];
	int		fd[2];
	pid_t	*pid;
	int		n_pipe = cmd->shell->mc_pipes;
	int		i=0;

	std_cpy[0] = dup(0);
	std_cpy[1] = dup(1);
	pid = malloc(sizeof(int) * n_pipe);
	while (i < n_pipe)
	{
		pipe(fd);
		if((pid[i]=fork())==0)
		{
			close(fd[0]);
			if (i == cmd->shell->mc_pipes - 1)
			{
				ft_printf("last pipe print sti on stdout");
				dup2(std_cpy[1], STDOUT_FILENO);
			}
			else
			{
				ft_printf("last pipe print sti on stdout");
				dup2(fd[1], STDOUT_FILENO);

			}
			close(fd[1]);
			ft_execvepipe(cmd);
			exit(0);
			// ft_executor(cmd->next);
		}
		else
		{
			dup2(fd[0],STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			// free_shell(cmd->shell);


		}
		i++;	
	}
	// dup2(std_cpy[0], STDIN_FILENO);
	// close(std_cpy[0]);
	// close(std_cpy[1]);
	i = -1;
	while (++i < n_pipe)
		waitpid(pid[i],&status,0);
	free(pid);
}