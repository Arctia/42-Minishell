#include "executor.h"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"

char	*ft_name(void)
{
	int		i;
	char	*name;
	char	*ihavetofree;

	i = 0;
	i++;
	ihavetofree = ft_itoa(i);
	name = ft_strjoin("tempfd_", ihavetofree);
	free(ihavetofree);
	return (name);
}

void	ft_less(t_command *cmd)												//	<
{
	int	fd;

	fd = open(cmd->next->command, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_redir(t_command *cmd)										//	>
{
	int	fd;

	fd = open(cmd->next->command,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_moremore(t_command *cmd) // lo so è sbajato ma fa piu' ride		//	>>
{
	int	fd;

	fd = open(cmd->next->command,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_heredoc(t_command *cmd)											//	<<
{
	char	*line;
	char	*delimiter;		//if you need mor var delete it
	int		fd;
	char	*filename;

	filename = ft_name();
	delimiter = cmd->next->command;
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && !ft_strcmp(delimiter, line))
	{
		// if(ar[QUOTE] || ar[DQUOTE])
		// 	ft_expander();				// i think we need it but maybe not
		write(fd, &line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	if (filename)
		free(filename);
	free(line);
	close(fd);
}
