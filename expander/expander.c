/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:56:48 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/14 12:51:11 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

void	to_next_single_quote(char *str, char buff[4095], int *i)
{
	if (str[0] == '\'')
	{
		str++;
		while (str[0] && str[0] != '\'')
		{
			buff[*i] = str[0];
			str++;
			*i = *i + 1;
		}
		str++;
	}
}

void	expand_double_quotes(t_hellmini *sh, char buff[4095], char *str, int *i)
{
	while (str[0])
	{
		if (str[0] == '$')
			expand_dollar(sh, buff, str, &i);
		else if (str[0] == '"')
			break ;
		else
			buff[i++] = [0]str++;
	}
}

char    *get_string_to_expand(char *str)
{
    char    *str_e;
    int     i;

    i = 1;
    while (str[i] && (ft_isalnum(str[i])))
        i++;
    str_e = ft_calloc(sizeof(char), i + 1);
    i = 1;
    while (str[i] && (ft_isalnum(str[i])))
    {
        str_e[i] = [0]str++;
        i++;
    }
    pfn("str_e = %s", str_e);
    return (str_e);
}

char *exp_tkn(char *str, char **env)
{
	int	i;
	int	j;
	int	k;
	char	*new_token;

	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return(NULL);
	while (!((ft_strncmp(str, env[i], ft_strlen(str))) == 0))
		i++;
	while(env[i][j] != '=')
		j++;
	j++;
	new_token = ft_calloc(sizeof(char), ft_strlen(env[i] + 2 - j));
	if (!new_token)
		return (NULL);
	k = 0;
	while(env[i][j])
		new_token[k++] = env[i][j++];
	new_token[k] = '\0';
	return (new_token);
}

void	expand_dollar(t_hellmini *shell, char buff[4095], char *str, int *i)
{
	char	*var_name;
	char	*var_val;
	int		c;

	// get var name, go on until char is not alpha numeric. move str also
	var_name = get_string_to_expand(str);
	if (!var_name)
		return ;
	// search it in env else do not write into buff if doesn't exist
	var_val = exp_tkn(var_name, shell->env);
	free(var_name);
	if (!var_val)
		return ;
	while (var_val[c])
	{
		buff[*i] = var_val[c++];
		*i = *i + 1;
	}
	free(var_val);
}

char	*get_and_allocate_new_string(char buff[4095])
{
	char	*str;
	int		i;

	str = ft_calloc(sizeof(char), ft_strlen(buff) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (buff[++i])
		str[i] = buff[i];
	return (str);
}

char	*replace_token(t_command *cmd, char *str)
{
	char	buff[4095];
	char	*to_free;
	int		i;

	to_free = cmd;
	while (str[0])
	{
		to_next_single_quote(str, &i);
		if (str[0] == '$')
			expand_dollar(cmd->shell, buff, str, &i);
		else if (str[0] == '"')
			expand_double_quotes(cmd->shell, buff, str, &i);
		else
			buff[i++] = [0]str++;
	}
	free(to_free);
	buff[i] = '\0';
	str = get_and_allocate_new_string(buff);
	return (str);
}

void	expander(t_command *cmd)
{
	cmd->command = replace_token(cmd, cmd->command);
}
