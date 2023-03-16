
#include "executor.h"

static void	print_free_close(char *str, int fd, DIR *dir)
{
	ft_printf("%s\n", str);
	if (fd != -1)
		close(fd);
	if (dir)
		closedir(dir);
	free(str);
}

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

/* maybe we need to store the string in fd, that way when using pipes
// it can print in recursive since errors are printed in an abdnormal
// way. */
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
	print_free_close(str, fd, dir);
	return (err);
}

void	execute_process(t_hellmini *shell, char *path, char **args)
{
	int	errno;

	errno = 0;
	if (path && ft_strchr(path, '/'))
		execve(path, args, shell->env);
	errno = error_print(path, args[0]);
	rl_clear_history();
	free_shell(shell);
	free(path);
	exit(errno);
}
