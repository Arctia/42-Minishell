/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:22:09 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:51:55 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
/*
	***********************************************************
					FT_APPEND
	***********************************************************
	working
	ret is allocated remember to free
*/

char	*ft_append(char *path, t_command *cmd)
{
	char	*ret;
	char	*retaux;
	char	*tmp;

	tmp = cmd->arguments[0];
	ret = malloc(sizeof(char ) * (ft_strlen(path)
				+ ft_strlen(cmd->arguments[0])) + 2);
	if (!ret)
		return (NULL);
	retaux = ret;
	while (*path)
		*ret++ = *path++;
	*ret++ = '/';
	while (*cmd->arguments[0])
		*ret++ = *cmd->arguments[0]++;
	*ret++ = '\0';
	cmd->arguments[0] = tmp;
	return (retaux);
}

/*
	***********************************************************
					FT_GETPATH
	***********************************************************
	working
	path da freeare
*/

char	**ft_getpath(t_command *cmd)
{
	char	**paths;
	char	*temp;

	temp = NULL;
	paths = NULL;
	temp = exp_tkn("PATH", cmd->shell->env);
	paths = ft_split(temp, ':');
	free(temp);
	return (paths);
}

/*
	***********************************************************
					FT_PATH_TO_USE
	***********************************************************
*/
static char	*path_to_use(char **paths, t_command *cmd, int id)
{
	char	*path;

	path = ft_append(paths[id - 1], cmd);
	ft_free_cmatrix(paths);
	return (path);
}

/*
	***********************************************************
					FT_FINDPATH
	***********************************************************
	working
	la i passata è una porcata ma su due piedi era la cosa piu''
	facile per essere a norma e non avere leak
*/
char	*ft_findpath(t_command *cmd, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**paths;

	paths = ft_getpath(cmd);
	ft_fixcommand(cmd);
	while (paths && paths[i++])
	{
		dir = opendir(paths[i - 1]);
		if (!dir)
			continue ;
		entry = readdir(dir);
		while (entry)
		{
			if (ft_strcmp(entry->d_name, cmd->arguments[0]))
			{
				closedir(dir);
				return (path_to_use(paths, cmd, i));
			}
			entry = readdir(dir);
		}
		closedir(dir);
	}
	ft_free_cmatrix(paths);
	return (NULL);
}
/*
	***********************************************************
					FT_FIXCOMMAND
	***********************************************************

*/

void	ft_fixcommand(t_command *cmd)
{
	char	*temp;
	char	*tmp;

	if (ft_strncmp("./", cmd->arguments[0], 2) == 0)
	{
		tmp = cmd->arguments[0];
		temp = ft_strtrim(cmd->arguments[0], "./");
		cmd->arguments[0] = temp;
		free(tmp);
	}
}
