
#include "redirection.h"

void	red_in(t_command *cmd, t_redir red, int *stdin)
{
	int	fd;

	if (red.n == red.lin)
		dup2(*stdin, STDIN_FILENO);
	fd = open(cmd->red[red.n], O_RDONLY);
	if (fd < 0)
	{
		cmd->red_error = red.n;
		set_ecode(1);
	}
	if (fd > 0 && red.n == red.lin && dup2(fd, STDIN_FILENO) < 0)
		ft_putstr_fd("minishell: dup2 Error\n", STDERR_FILENO);
	if (fd > 0)
		close(fd);
}

void	red_here_doc(t_command *cmd, t_redir red, int *stdin)
{
	char	*line;
	char	*delimiter;
	int		end[2];

	delimiter = cmd->red[red.n];
	if (red.n == red.lin)
		dup2(*stdin, STDIN_FILENO);
	pipe(end);
	line = readline(HEREDOC_MSG);
	while (line && !ft_strcmp(delimiter, line))
	{
		write(end[1], line, ft_strlen(line));
		write(end[1], "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (red.n == red.lin)
		dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
}

void	red_out(t_command *cmd, t_redir red, int *stdin, int *stdout)
{
	int	fd;

	if (cmd->red_error != -1)
	{
		close(*stdin);
		return ;
	}
	if (red.n == red.lout)
		dup2(*stdout, STDOUT_FILENO);
	fd = open(cmd->red[red.n], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		set_ecode(1);
	}
	if (fd > 0 && red.n == red.lout && cmd->red_error == -1
		&& dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: dup2 Error\n", STDERR_FILENO);
		set_ecode(1);
	}
	if (fd > 0)
		close(fd);
}

void	red_append(t_command *cmd, t_redir red, int *stdin, int *stdout)
{
	int	fd;

	if (cmd->red_error != -1)
	{
		close(*stdin);
		return ;
	}
	if (red.n == red.lout)
		dup2(*stdout, STDOUT_FILENO);
	fd = open(cmd->red[red.n], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		set_ecode(1);
	}
	if (fd > 0 && red.n == red.lout && cmd->red_error == -1
		&& dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: dup2 Error\n", STDERR_FILENO);
		set_ecode(1);
	}
	if (fd > 0)
		close(fd);
}
