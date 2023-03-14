/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:56:48 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/14 15:04:21 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global.h"

void	expand_dollar(t_hellmini *shell, char buff[4095], char *(*str), int *i);

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

void	expand_double_quotes(t_hellmini *sh, char buff[4095], char *(*str), int *i)
{
	if (*str[0] == '"')
	{
		(*str)++;
		while (*str[0] && *str[0] != '"')
		{
			if (*str[0] == '$')
				expand_dollar(sh, buff, str, i);
			else
			{
				buff[*i] = (*str)++[0];
				*i = *i + 1;
			}
		}
		(*str)++;
	}
}

char    *get_string_to_expand(char *(*str))
{
    char    *str_e;
    int     i;

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

char *exp_tkn(char *str, char **env)
{
	char	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return(NULL);
	while (env[i] && !((ft_strncmp(str, env[i], ft_strlen(str))) == 0))
		i++;
	if (!env[i])
		return (NULL);
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

void	expand_dollar(t_hellmini *shell, char buff[4095], char *(*str), int *i)
{
	char	*var_name;
	char	*var_val;
	int		c;

	var_name = get_string_to_expand(str);
	if (!var_name)
		return ;
	//pfn("0. %s", var_name);
	var_val = exp_tkn(var_name, shell->env);
	free(var_name);
	if (!var_val)
		return ;
	c = 0;
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
	return str;
}

char	*replace_token(t_command *cmd, char *(*str))
{
	char	buff[4095];
	//char	*to_free;
	int		i;

	//to_free = (*str);
	i = 0;
	while (*str[0])
	{
		to_next_single_quote(str, buff, &i);
		if (*str[0] == '\0')
			break;
		if (*str[0] == '$')
			expand_dollar(cmd->shell, buff, str, &i);
		else if (*str[0] == '"')
			expand_double_quotes(cmd->shell, buff, str, &i);
		else
		{
			buff[i++] = *str[0];
			(*str)++;
		}
	}
	//free(to_free); // maybe it needs to be freed out of there
	buff[i] = '\0';
	(*str) = get_and_allocate_new_string(buff);
	return (*str);
}

void	expander(t_command *cmd)
{
	int	i;

	cmd->command = replace_token(cmd, &(cmd->command));
	if (cmd->command && cmd->command[0])
		pfn("%t expanded command: %s", cmd->command);
	else
		pfn("%t expanded command: (null)");

	i = 0;
	while (cmd->arguments && cmd->arguments[i] && cmd->arguments[i][0])
	{
		cmd->arguments[i] = replace_token(cmd, &(cmd->arguments[i]));
		pfn("%t expanded argument[%d]: %s", i,cmd->arguments[i]);
		i++;
	}
	i = 0;
	/*while (cmd->red && cmd->red[i] && cmd->red[i][0])
	{
		cmd->red[i] = replace_token(cmd, &(cmd->red[i]));
		pfn("%t expanded red[%d]: %s", i,cmd->red[i]);
		i++;
	}*/
}
