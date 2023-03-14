#include "executor.h"

// typedef int	Pipe[2];

/*
	***********************************************************
					ft_execvepipe
	***********************************************************
	different ft_execv without fork i don't know if needed
*/

void	ft_execvepipe(t_command *cmd)
{
	char	*path;
	char	**arg;

	arg = ft_listtomatrix(cmd);
	path = ft_findpath(cmd, 0);
	if (execve(path, arg, cmd->shell->env) == -1)
		perror("execution failed");
	
	int i =-1;
	while (arg[++i])
		ft_printf("arg[%d]:%s",i,arg[i]);


	ft_free_cmatrix(arg);
	free(path);
	// exit(EXIT_FAILURE);
}


void	ft_pipe(t_command *cmd)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) < 0)
			perror("filed to create fd");
	if (!pid)
		ft_pipeline(cmd);
	while ((waitpid(0, &status, 0)) != -1)
		;

}


void	ft_pipejunior(int *fd)
{
	dup2(fd[1],1);
	close(fd[0]);
	close(fd[1]);
	return;
}

void	ft_pipeline(t_command *cmd)
{
	int		fd[2];
	pid_t	pid;
	int		n_pipe;

	n_pipe = cmd->shell->mc_pipes;
	while (n_pipe >= 1)
	{
		if (pipe(fd) != 0)
			perror("filed to create fd");
		if ((pid = fork()) < 0)
			perror("failed to fork");
		if (!pid)
		{
			ft_pipejunior(fd);
		}
		dup2(fd[0],0);
		close(fd[0]);
		close(fd[1]);
		n_pipe--;
	}
	ft_execvepipe(cmd);
}

