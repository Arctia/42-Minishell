
#include "executor.h"

static void print_free_close(char *str, int fd, DIR *dir)
{
	ft_printf("%s\n", str);
	close(fd);
	if (dir)
		closedir(dir);
	free(str);
}

static char *advanced_join(char *str, char *path)
{
	if (!path)
		return (str);
	return (ft_strjoin_free(str, path, 1, 0));
}

// maybe we need to store the string in fd, that way when using pipes
// it can print in recursive since errors are printed in an abdnormal
// way.
static int	error_print(char *path)
{
	char 	*str;
	DIR 	*dir;
	int		err;
	int		fd;

	fd = open(path, O_WRONLY);
	str = ft_strdup("minishell: ");
	dir = NULL;
	if (path)
		dir = opendir(path);
	str = advanced_join(str, path);
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
	errno = error_print(path);
	free_shell(shell);
	free(path);
	exit(errno);
}
