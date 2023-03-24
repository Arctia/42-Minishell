
#include "redirection.h"

static int	last_redir(t_command *cmd, int type)
{
	int	pos;
	int	n;

	pos = -1;
	n = -1;
	while (++n < (int) ft_arrlen(cmd->red_type))
	{
		if ((cmd->red_type[n] == REDIN || cmd->red_type[n] == HERDOC)
			&& type == 0)
			pos = n;
		else
			pos = n;
	}
	return (pos);
}

static void	stamp_no_file_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
}

static void	cycle_redirections(t_command *cmd, int *stdin, int *stdout)
{
	t_redir	red;

	red.n = 0;
	red.lin = last_redir(cmd, 0);
	red.lout = last_redir(cmd, 1);
	while (red.n < (int) ft_arrlen(cmd->red_type))
	{
		if (cmd->red_type[red.n] == REDIN)
			red_in(cmd, red, stdin);
		else if (cmd->red_type[red.n] == HERDOC)
			red_here_doc(cmd, red, stdin);
		else if (cmd->red_type[red.n] == REDOUT)
			red_out(cmd, red, stdin, stdout);
		else if (cmd->red_type[red.n] == REDAPP)
			red_append(cmd, red, stdin, stdout);
		red.n = red.n + 1;
	}
}

void	exec_redir(t_command *cmd, int *stdin, int *stdout)
{
	cycle_redirections(cmd, stdin, stdout);
	if (!cmd->red_error)
		ft_execv(cmd, &cmd->shell->exit_status);
	else
		stamp_no_file_error(cmd->red[cmd->red_error]);
	//if (last_redir(cmd, 0) > -1)
	//	dup2(*stdout, STDOUT_FILENO);
	dup2(*stdin, STDIN_FILENO);
	close(*stdin);
	close(*stdout);
}
