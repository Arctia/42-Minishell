
#include "./expander.h"

void	expand_tilde(t_hellmini *sh, char buff[4095], char *(*str), int *i)
{
	char	*home;
	int		c;

	home = NULL;
	if (!((*str)[0] == '~' && ((*str)[1] == '/' || !((*str)[1]))))
		return ;
	home = exp_tkn("HOME", sh->env);
	c = 0;
	while (home[c])
	{
		buff[*i] = home[c++];
		*i = *i + 1;
	}
	(*str)++;
	ft_free_ptr(home);
}

int	expand_question(t_hellmini *sh, char buff[4095], char *(*str), int *i)
{
	char	*value;
	int		c;

	value = NULL;
	if ((*str)[1] != '?')
		return (FALSE);
	pfn("expanding_question: *g_error_code [%d]", *g_error_code);
	value = ft_itoa(*g_error_code);
	pfn("expanding_question: *g_error_code [%d]", *g_error_code);
	c = 0;
	while (value[c])
	{
		buff[*i] = value[c++];
		*i = *i + 1;
	}
	(*str)++;
	(*str)++;
	ft_free_ptr(value);
	return (TRUE);
}

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
	while ((*str)[i] && ((ft_isalnum((*str)[i])) || (*str)[i] == '_'))
		i++;
	str_e = ft_calloc(sizeof(char), i);
	i = 0;
	(*str)++;
	while ((*str)[0] && ((ft_isalnum((*str)[0])) || (*str)[0] == '_'))
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
	new_token = ft_calloc(sizeof(char), ft_strlen(env[i]) + 1);
	if (!new_token)
		return (NULL);
	k = 0;
	while (env[i][j])
		new_token[k++] = env[i][j++];
	new_token[k] = '\0';
	return (new_token);
}
