#include "../global.h"

int	ms_expcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0)
	{
		if (s2[i] && s1[i] != s2[i] && s1[i + 1] && s1[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

int envcpy_len(int len, char **new_env)
{
	new_env = ft_calloc(sizeof(char *), len);
	if (!new_env)
		return(-1);
	return (0);
}

void	envcpy_line(char *line, char **new_line)
{
	int	i;

	i = 0;
	while(line[i] != 0)
		i++;
	*new_line = ft_calloc(sizeof(char), i + 1);
	if (!(*new_line))
		return ;
	i = 0;
	while(line[i] != 0)
	{
		(*new_line)[i] = line[i];
		i++;
	}
}

char *get_next_arg(char **args, int first_time)
{
	static int	i;

	if (!i || !first_time)
		i = 0;
	return (args[i++]);
}

int	unset(t_command *com)
{
	char	**new_env;
	int		lenght;
	char	*arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lenght = ft_cmtxlen(com->shell->env);
	envcpy_len(lenght - 1, new_env);
	arg = get_next_arg(com->arguments, 0);
	while (arg)
	{
		while (lenght > i)
		{
			if (!ms_expcmp(com->shell->env[i], arg))
				envcpy_line(com->shell->env[i], &new_env[j++]);
			i++;
		}
		arg = get_next_arg(com->arguments, 1); 
	}
	ft_free_cmatrix(com->shell->env);
	com->shell->env = new_env;
	return (0);
}
