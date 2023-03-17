#include "executor.h"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"

void	ft_chooseredir(t_command *cmd)
{
	if (cmd->red_type[0] == HERDOC)			//<<
		ft_heredoc(cmd);
	else if (cmd->red_type[0] == REDIN)		//<
		ft_redin(cmd);
	else if (cmd->red_type[0] == REDOUT)	//>
		ft_redout(cmd);
	else if (cmd->red_type[0] == REDAPP)	//>>
		ft_redappend(cmd);
}

int	ft_redir(t_command * cmd)
{
	pid_t	pid;
	int		stdin_cpy = dup(0); // maybe better STD...
	int		stdout_cpy = dup(1); // maybe better STD...
	char	**redreset;
	int		*typereset;

	redreset = cmd->red;
	typereset = cmd->red_type;
	// ft_printf("print matrix\n");
	ft_print_matrix(cmd->red);
	while (*cmd->red && *cmd->red_type)		//cmd->spc[HEREDOC]?
	{
		ft_chooseredir(cmd);
		// ft_printf("cmd red: %s\n",*cmd->red);
		// ft_printf("cmd red type %d\n",*cmd->red_type);
		*cmd->red++;
		*cmd->red_type++;
		// ft_printf("++cmd red: %s\n",*cmd->red);
		// ft_printf("++cmd red type %d\n",*cmd->red_type);
	}
	ft_execv(cmd,pid,&cmd->shell->exit_status);
	if(cmd->red_type[0] != REDIN)
		dup2(stdout_cpy, STDOUT_FILENO);
	dup2(stdin_cpy, STDIN_FILENO);
	cmd->red = redreset;
	cmd->red_type = typereset;
	return (0);
}


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

void	ft_redin(t_command *cmd)												//	<
{
	int	fd;

	fd = open(*cmd->red, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such fiale or directory\n",
			STDERR_FILENO);
		// exit(0);
		// (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
		// exit(0);
		// (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
}

void	ft_redout(t_command *cmd)										//	>
{
	int	fd;

	fd = open(*cmd->red,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		exit(0);
		//  (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
		exit(0);  
		//  (EXIT_FAILURE);
	}		
	if (fd > 0)
		close(fd);
}

void	ft_redappend(t_command *cmd) // lo so è sbajato ma fa piu' ride		//	>>
{
	int	fd;

	fd = open(*cmd->red,
			O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
		//  (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
		//  (EXIT_FAILURE);
	}		
	if (fd > 0)
		close(fd);
}

void	ft_heredoc(t_command *cmd)											//	<<
{
	char	*line;
	char	*delimiter;		//if you need more var delete it
	int		fda;
	char	*filename;

	filename = ft_name();
	delimiter = *cmd->red;
	fda = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && !ft_strcmp(delimiter, line))
	{
		// if(ar[QUOTE] || ar[DQUOTE])
		// 	ft_expander();				// i think we need it but maybe not
		write(fda, &line, ft_strlen(line));
		write(fda, "\n", 1);
		free(line);
	}
	// dup2(fda, STDOUT_FILENO);
	if (cmd->red[1])
	{
		// ft_printf("i'm here");
		if (fda < 0)
		{
			ft_putstr_fd("minishell: heredoc: Error\n", STDERR_FILENO);
			//  (EXIT_FAILURE);
		}
		if (fda > 0 && dup2(fda, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
			//  (EXIT_FAILURE);
		}		
		if (fda > 0)
			close(fda);
	}
	if (filename)
		free(filename);
	free(line);
}
