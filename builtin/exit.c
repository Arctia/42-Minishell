#include "../global.h"

int	check_exit_argument(char *com)
{
	unsigned int	i;

	i = ft_strlen(com);
	if (i > 19)
		return (-1);
	while (i >= 0)
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

int	ms_exit(t_command *cmd)
{
	int	ret;

	ret = 0;
	if (!(!(cmd->arguments[2]))) //questa è per vincenzo
	{
		printf("exit\nexit: too many arguments\n");
		ret = 255;
	}
	else if (check_exit_arguments(cmd->arguments[1]) != 0)
	{
		pfn("exit\nexit: %s: numeric argument required", cmd->arguments[1]);
		ret = 255;
	}
	else
	{
		ret = ft_atoll(cmd->arguments);
		ret %= 256 + 256 * (ret < 0);
	}
	free_shell(cmd->shell);
	exit (ret);
}
