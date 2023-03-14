#include "executor.h"

// typedef int	Pipe[2];

/*
	***********************************************************
					ft_execvepipe
	***********************************************************
	different ft_execv without fork i don't know if needed
*/

void ft_pipe(t_command *cmd)
{
	pid_t	pid;
	int		fd[2];
	int		tmp_fd = dup(STDIN_FILENO);
	int		n_pipes = cmd->shell->mc_pipes+1;
	while (n_pipes--)
	{

		pipe(fd);
		if ((pid = fork()) == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			ft_execvepipe(cmd,tmp_fd);
		}
		// else
		// {
		// 	close(fd[1]);
		// 	close(tmp_fd);
		// 	tmp_fd = fd[0];
		// }
}
}

void ft_execvepipe(t_command *cmd, int tmp_fd)
{
	char	*path;
	char	**arg;

	arg = ft_listtomatrix(cmd);
	path = ft_findpath(cmd, 0);

	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	if (execve(path, arg, cmd->shell->env) == -1)
		perror("execution failed");
}
