#include "executor.h"
/*
	***********************************************************
					ft_pipe
	***********************************************************
	da testare expader
*/

void	ft_pipe(t_command *cmd, int std_cpy[2], pid_t pid)
{
	int			**fd;
	int			i;
	t_command	*reset;

	reset = cmd;
	i = -1;
	fd = malloc(sizeof(int *) * (cmd->shell->mc_pipes + 1));
	while (++i < cmd->shell->mc_pipes + 1)
		fd[i] = ft_calloc(sizeof(int), 2);
	i = 0;
	while (cmd && (cmd->spc[PIPE] || cmd->prev->spc[PIPE]))
	{
		// expander(cmd);
		pipe(fd[i]);
		pid = fork();
		if (!pid)
			ft_child(cmd, fd, &i, std_cpy);
		dup2(fd[i][0], STDIN_FILENO);
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		cmd = cmd->next;
		i++;
	}
	ft_wait(i);
	dup2(std_cpy[0], STDIN_FILENO);
	close(std_cpy[0]);
	close(std_cpy[1]);
	cmd = reset;
	free(fd);
}
/*
	***********************************************************
					ft_child
	***********************************************************
*/

void	ft_child(t_command *cmd, int **fd, int *i, int std_cpy[2])
{
	close(fd[*i][0]);
	if (cmd->spc[PIPE])
	{
		dup2(fd[*i][1], STDOUT_FILENO);
		close(fd[*i][1]);
	}
	else
	{
		dup2(std_cpy[1], STDOUT_FILENO);
		close(std_cpy[1]);
	}
	if (cmd->red_type != NULL)
		ft_redirpipe(cmd, &std_cpy[0], &std_cpy[1]);
	ft_execv(cmd, &cmd->shell->exit_status);
	// free_shell(cmd->shell);
	exit(1);
}
/*
	***********************************************************
					ft_wait
	***********************************************************
*/

void	ft_wait(int i)
{
	while (i > 0)
	{
		waitpid(-1, 0, 0);
		i--;
	}
}
