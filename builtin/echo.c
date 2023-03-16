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
		write (fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	echo_aux(int argc, char **argv, t_command *cmd)
{
	int	n;

	n = 0;
	while (n < argc - 1)
	{
		str_add(cmd->args[n], argv[n + 1]);
		n++;
	}
	return (0);
}

int	echo_engine(t_command *cmd)
{
	int	n_flag;
	int	n;

	shell->to_ret = 0;
	n_flag = 0;
	n = 0;
	echo_aux(argc, argv, cmd);
	while (!ft_strncmp(cmd->arguments[++n], "-n", 3))
		n_flag = 1;
    n = 0;
	while (cmd->arguments)
	{
		put_str_fd(cmd->arguments[n], 1);
        n++
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (shell->to_ret);
}
