#include "executor.h"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"

void	ft_chooseredir(t_command *cmd)
{
	int i=0;
	i++;
	ft_printf("choose giro : %d\n",i);
	if (cmd->spc[REDIN]) //<
		ft_redin(cmd);
	if (cmd->spc[REDOUT]) //>
		ft_redout(cmd);
	if (cmd->spc[REDAPP])	//>>
		ft_redappend(cmd);
	// cmd = cmd->next;
	// if (cmd->spc[HERDOC])	//<<
	// 	ft_heredoc(cmd);
}

int	ft_redir(t_command * cmd)
{
	pid_t	pid;
	int	stdin_cpy = dup(0); // maybe better STD...
	int fd[2];
	char	**reset;
	reset = cmd->red;
	while (cmd && (cmd->spc[REDIN] || cmd->spc[REDOUT] || cmd->spc[REDAPP]))		//cmd->spc[HEREDOC]?
	{
		int i =0;
		i++;
		ft_printf("ciack si gira %d\n",i);
		// pipe(fd);
		// close(fd[0]);
		// if (cmd->spc[REDIN] || cmd->spc[REDOUT] || cmd->spc[REDAPP])
		// 	dup2(fd[1], STDOUT_FILENO);
		// else
		// 	dup2(stdin_cpy, STDOUT_FILENO);
	// ft_printf("mauraaaaaaaaaaaaaaaaaaaa");
	ft_printf("in while pria cmd: %s\n",cmd->command);
		// close(fd[1]);
		ft_chooseredir(cmd);
	ft_printf("in while post cmd: %s\n",cmd->command);

		// if (cmd->next)
		// if(cmd->next==NULL)
		// 	break;
	// ft_printf("mauroooooooooooooooooooo");
	ft_printf("cmd: %s\n",cmd->command);
	
		cmd = cmd->next;
	ft_printf("cmd.next: %s\n",cmd->command);

	}
	ft_printf("cmd: %s\n",cmd->command);

	ft_printf("cmd.prev.prev:%s'n",cmd->prev->prev->command);
	ft_printf("cmd.prev:%s\n",cmd->prev->command);
	cmd = cmd->prev;
	cmd->red = reset;
	ft_execv(cmd,pid,&cmd->shell->exit_status);

	// if(cmd && (!cmd->prev->spc[PIPE]))
	// {
	// 	ft_execv(cmd,pid,&cmd->shell->exit_status);
	// 	return (1);
	// }
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
	int	file;

	int i=0;
	i++;
	// ft_printf("giro : %d\n",i);
	file = open(*cmd->red++, O_RDONLY);
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

void	ft_redout(t_command *cmd)										//	>
{
	int	file;
	int i=0;
	i++;
	ft_printf("giro : %d\n",i);


	ft_printf("pria cmd.red:%s\n",*cmd->red);

	file = open(*cmd->red++,
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	// *cmd->red++;
	
	ft_printf("post cmd.red:%s\n",*cmd->red);
	// if (file < 0)
	// {
	// 	ft_putstr_fd("minishell: outfile: Error\n", STDERR_FILENO);
	// 	// exit(0);
	// 	//  (EXIT_FAILURE);
	// }
	// dup2(file, STDOUT_FILENO);
	// if (file > 0 && dup2(file, STDOUT_FILENO) < 0)
	// {
	// 	ft_putstr_fd("minishell: pipe Error\n", STDERR_FILENO);
	// 	// exit(0);
	// 	//  (EXIT_FAILURE);
	// }		
	// // if (file > 0)
	// 	close(file);
	// exit(0);
}

void	ft_redappend(t_command *cmd) // lo so è sbajato ma fa piu' ride		//	>>
{
	int	file;

	file = open(*cmd->red++,
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
	delimiter = *cmd->red;
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
