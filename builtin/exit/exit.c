//#include "../global.h"
#include <stdio.h>

int	ft_isdigit(char *com)
{
	if (ch <= '9' && ch >= '0')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_exit_argument(char *com)
{
	unsigned int i;

	i = ft_strlen(com);
	if (i > 19)
		return (-1);
	while (i => 0)
	{
		i--;
		if (!(ft_isdigit(com[i])) && i > 0)
			return (-1);
		else if (i == 0)
		{
			if ((ft_isdigit(com[i])))
				return (0);
			else if (com[i] == "-")
				return (0);
			else
				return (-1);
		}
	}
	return (0);
}

int	check_spaces(const char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	return (i);
}

long long	ft_atoll(const char *str)
{
	long	i;
	long	sign;
	long	res;

	i = check_spaces(str);
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int exit(t_command *cmd)
{
	int n;
	int	ret;

	n = 0;
	ret = 0;
	if (!(!(cmd->arguments[2]))) //questa è per vincenzo
	{
		printf("exit: too many arguments\n");
		return (255);
	}
	if (check_exit_arguments(com->arguments[1]) != 0)
		return (255);
	ret = ft_atoll(cmd->arguments);
	free_shell
	ret %= 256 + 256 * (ret < 0);
	return (ret);
}
