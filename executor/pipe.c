#include "executor.h"

/*
	***********************************************************
					ft_pipe
	***********************************************************
	no pid array
	mancano ft_expander, ft_redir(ancora da scrivere) ft_builtin
	cat | ls singolo funzionaaaaaaa zi puo'fareeeeeeeeeeeeeee
	cat | cat | ls quasi funzione devi premere due volte invio 
	ma non printa i due \n ma uno solo 

*/

void	ft_pipe(t_command *cmd)
{
	int		std_cpy[2];
	int		fd[2];
	pid_t		pid;

	std_cpy[0] = dup(0);	// input
	std_cpy[1] = dup(1);	//	output
	while (cmd && (cmd->spc[PIPE] || cmd->prev->spc[PIPE]))
	{
		pipe(fd);
		pid = fork();
		if(!pid)
		{
			close(fd[0]);
			if (cmd->spc[PIPE])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			else
			{
				dup2(std_cpy[1], STDOUT_FILENO);
				close(std_cpy[1]);
			}
			ft_execv(cmd, pid, &cmd->shell->exit_status);
			waitpid(pid,0,0);
			exit(1);
			// if(cmd->next = NULL)
				// while(waitpid(pid, 0, 0))
					// ;
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		cmd = cmd->next;
	}
	// waitpid(pid, 0, 0);
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
	pid = malloc(sizeof(int) * n_pipe + 1);
	while (cmd && (cmd->spc[PIPE] || cmd->prev->spc[PIPE]))
	{
		pipe(fd);
		if((pid[i]=fork())==0)
		{
			close(fd[0]);
			if (cmd->spc[PIPE])
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			else
			{
				dup2(std_cpy[1], STDOUT_FILENO);
				close(std_cpy[1]);
			}
			// break;
			ft_execv(cmd,pid[i],&status);
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
	// if(pid==0)
	// 	ft_execv(cmd,pid[i],&status);
	// else
	// {
		dup2(std_cpy[0], STDIN_FILENO);
		close(std_cpy[0]);
		close(std_cpy[1]);
		i = -1;
		while (++i < n_pipe)
			waitpid(pid[i],&status,0);
		free(pid);
	// }
}