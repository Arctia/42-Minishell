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

char	**envcpy_len(int len, char **new_env)
{
	new_env = ft_calloc(sizeof(char *), len + 1);
	if (!new_env)
		return (NULL);
	return (new_env);
}

char	*envcpy_line(char *line)
{
	char	*new_line;
	int		i;

	i = 0;
	while(line[i] != 0)
		i++;
	new_line = ft_calloc(sizeof(char), i + 1);
	if (!(new_line))
		return (NULL);
	i = 0;
	while(line[i] != 0)
	{
		(new_line)[i] = line[i];
		i++;
	}
	return (new_line);
}

char *get_next_arg(char *arg)
{
	arg = ft_strjoin_free(arg, "=", 1, 0);
	return (arg);
}

int	cmp_arguments(char *env_string, char **args)
{
	char	*arg;
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (args[i])
	{
		arg = ft_strjoin(args[i++], "=");
		if (!ft_strncmp(arg, env_string, ft_strlen(arg)))
		{
			pfn("found");
			free(arg);
			return (1);
		}
		free(arg);
	}
	return (0);
}

int	unset(t_command *com)
{
	char	**new_env;
	int		lenght;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lenght = ft_cmtxlen(com->shell->env);
	new_env = envcpy_len(lenght, new_env);
	if (ft_cmtxlen(com->arguments) > 1)
	{
		while (lenght > i)
		{
			if (!cmp_arguments(com->shell->env[i], com->arguments))
				new_env[j++] = envcpy_line(com->shell->env[i]);
			i++;
		}
	}
	ft_free_cmatrix(com->shell->env);
	com->shell->env = new_env;
	return (0);
}
