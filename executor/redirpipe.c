#include "executor.h"
#define HEREDOC_MSG	"\033[1;97m> \033[0m"
/*
	***********************************************************
					ft_redir
	***********************************************************
*/
int	ft_redir(t_command *cmd, int *stdin_cpy, int *stdout_cpy)
{
	while (*cmd->red && cmd->red_type)
	{
		ft_chooseredir(cmd, stdin_cpy, stdout_cpy);
		cmd->red++;
		cmd->red_type++;
	}
	ft_execv(cmd, &cmd->shell->exit_status);
	if (cmd->red_type[0] != REDIN)
		dup2(*stdout_cpy, STDOUT_FILENO);
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	close(*stdout_cpy);
	return (0);
}
/*
	***********************************************************
					ft_redirpipe
	***********************************************************
*/

void	ft_redirpipe(t_command *cmd, int *stdin_cpy, int *stdout_cpy)
{
	char	**redreset;
	int		*typereset;

	redreset = cmd->red;
	typereset = cmd->red_type;
	while (*cmd->red && cmd->red_type)
	{
		ft_chooseredir(cmd, stdin_cpy, stdout_cpy);
		cmd->red++;
		cmd->red_type++;
	}
	cmd->red = redreset;
	cmd->red_type = typereset;
}
/*
	***********************************************************
					ft_chooseredir
	***********************************************************
*/

void	ft_chooseredir(t_command *cmd, int *stdin_cpy, int *stdout_cpy)
{
	if (cmd->red_type[0] == HERDOC)
		ft_heredoc(cmd, stdin_cpy);
	else if (cmd->red_type[0] == REDIN)
		ft_redin(cmd, stdin_cpy);
	else if (cmd->red_type[0] == REDOUT)
		ft_redout(cmd, stdout_cpy);
	else if (cmd->red_type[0] == REDAPP)
		ft_redappend(cmd, stdout_cpy);
}
