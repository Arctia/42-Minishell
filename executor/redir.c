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
	int	file;

	file = open(cmd->next->command, O_RDONLY);
	if (file < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		// (EXIT_FAILURE);
	}
	if (file > 0 && dup2(file, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
		// (EXIT_FAILURE);
	}
	if (file > 0)
		close(file);
}

void	ft_redir(t_command *cmd)										//	>
{
	int	file;

	file = open(cmd->next->command,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		//  (EXIT_FAILURE);
	}
	if (file > 0 && dup2(file, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
		//  (EXIT_FAILURE);
	}		
	if (file > 0)
		close(file);
}

void	ft_moremore(t_command *cmd) // lo so è sbajato ma fa piu' ride		//	>>
{
	int	file;

	file = open(cmd->next->command,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (file < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		//  (EXIT_FAILURE);
	}
	if (file > 0 && dup2(file, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
		//  (EXIT_FAILURE);
	}		
	if (file > 0)
		close(file);
}

void	ft_heredoc(t_command *cmd)											//	<<
{
	char	*line;
	char	*delimiter;		//if you need more var delete it
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
