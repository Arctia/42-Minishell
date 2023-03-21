#include "../global.h"

static int	ft_strlen_tochar(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != '\n')
		i++;
	return (i);
}

// return 1 if exists and needs to be replaced, 
//			2 if exists but shouldn't be replaced.
static int	compare_values(char *entry, char *arg)
{
	int	e_size;
	int	a_size;

	if (ft_strlen_tochar(entry, '=') != ft_strlen_tochar(arg, '='))
		return (0);
	if (ft_strncmp(entry, arg, ft_strlen_tochar(arg, '=')))
		return (0);
	else
	{
		if (ft_strchr(arg, '='))
			return (1);
		else
			return (2);
	}
	return (0);
}

char	**insert_values_env(char **args, char **env)
{
	int	exist;
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (env[j])
		{
			exist = compare_values(env[j], args[i]);
			if (exist == 1)
			{
				free(env[j]);
				env[j] = ft_strdup(args[i]);
			}
			if (exist)
				break ;
			j++;
		}
		if (j >= ft_cmtxlen(env))
			env[j] = ft_strdup(args[i]);
		i++;
	}
	return (env);
}
