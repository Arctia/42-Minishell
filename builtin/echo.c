#include "./../global.h"

int	str_add(char *str1, const char *str2)
{
	int	i;

	i = 0;
	while(str2[i])
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (0);
}

int	put_str_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	write(fd, " ", 1);
	return (i);
}

int	echo_engine(t_command *cmd)
{
	int	n_flag;
	int	n;

	cmd->shell->exit_status = 0;
	n_flag = 0;
	n = 1;
	while (!ft_strncmp(cmd->arguments[n++], "-n", 3))
	{
		n_flag = 1;
		break ;
	}
    n = 1;
    while (cmd->arguments && ft_strncmp(cmd->arguments[++n], "-n", 3))
	while (cmd->arguments && cmd->arguments[n])
		put_str_fd(cmd->arguments[n++], 1);
	if (!n_flag)
		write(1, "\n", 1);
	return (cmd->shell->exit_status);
}
