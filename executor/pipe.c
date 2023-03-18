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
	int	pid = 10;
	int			std_cpy[2];
	int			**fd;
	int			i = -1;

	std_cpy[0] = dup(0);
	std_cpy[1] = dup(1);
	fd = malloc(sizeof(int *) * cmd->shell->mc_pipes);
	while(++i < 2)
		fd[i] = ft_calloc(sizeof(int), PATH_MAX);

	i = 0;
	while (cmd && (cmd->spc[PIPE] || cmd->prev->spc[PIPE]))
	{
		pipe(fd[i]);
		ft_printf("ï'hehre\n");
		if(!fork())
		{
			close(fd[i][0]);
			if (cmd->spc[PIPE])
			{
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			else
			{
				dup2(std_cpy[1], STDOUT_FILENO);
				close(std_cpy[1]);
			}
			ft_execv(cmd, pid, &cmd->shell->exit_status);
			exit(1);
		}
		dup2(fd[i][0], STDIN_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);

		cmd = cmd->next;
		i++;
	}
	while (i > 0)
	{
		waitpid(-1, 0, 0);
		i--;
	}
	dup2(std_cpy[0], STDIN_FILENO);
	close(std_cpy[0]);
	close(std_cpy[1]);

}

void	ft_dupandclose(int std_cpy[2], int **fd, int i, pid_t pid)
{
	// int		std_cpy[2];
	if (i == 0)
	{
		std_cpy[0] = dup(0);	// input
		std_cpy[1] = dup(1);	//	output
		// return (std_cpy[2]);
	}
	else if (i == 1)
	{
		close(std_cpy[0]);
		close(std_cpy[1]);
	}
	else if (pid != 0 && i == 2)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
	

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