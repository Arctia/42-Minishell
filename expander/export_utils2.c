#include "../global.h"

int	ft_strchr_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (i >= (int) ft_strlen(str))
		return (-1);
	return (i);
}

int	ft_strcmp_better(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

void	print_env_vars(char *env_cpy)
{
	int		i;
	int		k;
	char	tmp[4095];

	i = -1;
	k = -1;
	while (env_cpy[++i])
	{
		if (env_cpy[i] == '=')
		{
			tmp[++k] = env_cpy[i];
			tmp[++k] = '"';
		}
		else if (env_cpy[i] == '"')
		{
			tmp[++k] = '\\';
			tmp[++k] = env_cpy[i];
		}
		else
			tmp[++k] = env_cpy[i];
	}
	tmp[++k] = '"';
	tmp[++k] = '\n';
	tmp[++k] = '\0';
	ft_putstr_fd(tmp, 1);
}
