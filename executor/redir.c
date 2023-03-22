#include "executor.h"
#define HEREDOC_MSG	"\033[1;97m> \033[0m"
// # define HEREDOC_MSG	"\033[1;37m> \033[0m"

/*
	***********************************************************
					ft_redin	//	<
	***********************************************************
*/
void	ft_redin(t_command *cmd, int *stdin_cpy)
{
	int	fd;

	dup2(*stdin_cpy, STDIN_FILENO);
	fd = open(*cmd->red, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		if (cmd->spc[PIPE])
			exit(1);
		else
			return ;
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
	}
	if (fd > 0)
		close(fd);
}
/*
	***********************************************************
					ft_redout	//	>
	***********************************************************
*/

void	ft_redout(t_command *cmd, int *stdout_cpy)
{
	int	fd;

	dup2(*stdout_cpy, STDOUT_FILENO);
	fd = open(*cmd->red,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		set_ecode(1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: dup2 Error\n", STDERR_FILENO);
		set_ecode(1);
	}		
	if (fd > 0)
		close(fd);
}
/*
	***********************************************************
					ft_redappend	//	>>
	***********************************************************
*/

void	ft_redappend(t_command *cmd, int *stdout_cpy)
{
	int	fd;

	dup2(*stdout_cpy, STDOUT_FILENO);
	fd = open(*cmd->red,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		set_ecode(1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: dup2 Error\n", STDERR_FILENO);
		set_ecode(1);
	}		
	if (fd > 0)
		close(fd);
}
/*
	***********************************************************
					ft_heredoc	//	<<
	***********************************************************
*/

void	ft_heredoc(t_command *cmd, int *stdin_cpy)
{
	char	*line;
	char	*delimiter;
	int		end[2];

	dup2(*stdin_cpy, STDIN_FILENO);
	delimiter = *cmd->red;
	pipe(end);
	line = readline(HEREDOC_MSG);
	while (line && !ft_strcmp(delimiter, line))
	{
		write(end[1], line, ft_strlen(line));
		write(end[1], "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
}
