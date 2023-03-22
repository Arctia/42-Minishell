/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:57 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:21:58 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../glob.h"
/*
	***********************************************************
					print_free_close
	***********************************************************
*/
static void	print_free_close(char *str, int fd, DIR *dir, int err)
{
	set_ecode(err);
	ft_printf("%s\n", str, err);
	if (fd != -1)
		close(fd);
	if (dir)
		closedir(dir);
	free(str);
}
/*
	***********************************************************
					advanced_join
	***********************************************************
*/

static char	*advanced_join(char *str, char *path, char *cmd_name)
{
	if (!path)
	{
		if (cmd_name)
			return (ft_strjoin_free(str, cmd_name, 1, 0));
		return (str);
	}
	return (ft_strjoin_free(str, path, 1, 0));
}
/*
	***********************************************************
					pen_paths
	***********************************************************
*/

static DIR	*open_paths(char *path, int *fd)
{
	DIR	*dir;

	*fd = 0;
	dir = NULL;
	if (path != NULL && ft_strchr(path, '/'))
	{
		*fd = open(path, O_WRONLY);
		dir = opendir(path);
	}
	return (dir);
}
/*
	***********************************************************
					error_print
	***********************************************************
	maybe we need to store the string in fd, that way when using pipes
	it can print in recursive since errors are printed in an abdnormal
	way.
 */

static int	error_print(char *path, char *cmd_name)
{
	char	*str;
	DIR		*dir;
	int		err;
	int		fd;

	fd = 0;
	str = ft_strdup("minishell: ");
	dir = open_paths(path, &fd);
	str = advanced_join(str, path, cmd_name);
	if (path == NULL || ft_strchr(path, '/') == NULL)
		str = ft_strjoin_free(str, ": command not found", 1, 0);
	else if (fd == -1 && dir == NULL)
		str = ft_strjoin_free(str, ": No such file or directory", 1, 0);
	else if (fd == -1 && dir != NULL)
		str = ft_strjoin_free(str, ": is a directory", 1, 0);
	else if (fd != -1 && dir == NULL)
		str = ft_strjoin_free(str, ": Permission denied", 1, 0);
	if ((!path || !ft_strchr(path, '/')) || (fd == -1 && !dir))
		err = ERR_UNK;
	else
		err = ERR_DIR;
	print_free_close(str, fd, dir, err);
	return (err);
}
/*
	***********************************************************
					execute_process
	***********************************************************
*/

void	execute_process(t_hellmini *shell, char *path, char **args)
{
	int	errnoa;

	errnoa = 0;
	signal(SIGINT, control_slash);
	signal(SIGQUIT, control_slash);
	if (execve(path, args, shell->env))
		errnoa = error_print(path, args[0]);
	clear_history();
	free_shell(shell);
	free(path);
	exit(errnoa);
}
