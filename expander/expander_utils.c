
#include "./expander.h"

void	to_next_single_quote(char *(*str), char buff[4095], int *i)
{
	if (*str[0] == '\'')
	{
		(*str)++;
		while (*str[0] && *str[0] != '\'')
		{
			buff[*i] = *str[0];
			(*str)++;
			*i = *i + 1;
		}
		(*str)++;
	}
}

char	*get_string_to_expand(char *(*str))
{
	char	*str_e;
	int		i;

	i = 1;
	while ((*str)[i] && (ft_isalnum((*str)[i])))
		i++;
	str_e = ft_calloc(sizeof(char), i);
	i = 0;
	(*str)++;
	while ((*str)[0] && (ft_isalnum((*str)[0])))
	{
		str_e[i] = ((*str)++)[0];
		i++;
	}
	return (str_e);
}

char	*exp_tkn(char *str, char **env)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return (NULL);
	while (env[i] && !((ft_strncmp(str, env[i], ft_strlen(str))) == 0))
		i++;
	if (!env[i])
		return (NULL);
	while (env[i][j] != '=')
		j++;
	j++;
	new_token = ft_calloc(sizeof(char), ft_strlen(env[i] + 2 - j));
	if (!new_token)
		return (NULL);
	k = 0;
	while (env[i][j])
		new_token[k++] = env[i][j++];
	new_token[k] = '\0';
	return (new_token);
}

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}
