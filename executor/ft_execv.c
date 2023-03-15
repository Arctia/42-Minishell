#include "executor.h"

/*
	***********************************************************
					FT_LISTTOMATRIX
	***********************************************************
	working
	arg is allocated remember to free
	there is both t_command both t_hellmini perchè pe testa non 
	know how to do
*/

char	**ft_listtomatrix(t_command *cmd)
{
	char	**arg;
	int		i;
	int		j;

	arg = NULL;
	i = 1;
	j = 0;
	if (cmd->arguments)
		while (cmd->arguments[j++])
			i++;
	arg = ft_calloc(sizeof(char *), i + 1);
	if (!arg)
		return (NULL);
	arg[0] = ft_strdup(cmd->command);
	i = 1;
	j = -1;
	while (cmd->arguments[++j])
		arg[i++] = ft_strdup(cmd->arguments[j]);
	arg[i++] = NULL;
	return (arg);
}

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

char	**ft_getpath_old(t_command *cmd, int i)
{
	char	**ritemp;
	char	**path;
	char	*temp;
	char	cwd[MAXPATHLEN];

	ritemp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		;
	else
		perror("getcwd() error");
	while (cmd->shell->env[i])
	{
		if (ft_strncmp("PATH", cmd->shell->env[i], 4) == 0)
		{
			temp = ft_strtrim(cmd->shell->env[i], "PATH=");
			if (ft_strncmp("./", cmd->arguments[0], 2) == 0)
				ritemp = ft_split(temp, ':');
			else
				path = ft_split(temp, ':');
			free(temp);
			break ;
		}
		i++;
	}
	if (ritemp)
	{
		path = ft_addlinetomatrix(ritemp, cwd);
		free(ritemp);
	}
	return (path);
}

int	and_slash(char *str)
{
	str++;
	pfn("%t *str:%s", str);
	while (str[0])
	{
		if (str[0] == '/')
			return (1);
		str++;
	}
	pfn("%1t end *str:%s", str);
	return (0);
}

//char	**remove_double_points(char **paths, t_command *cmd)
//{
	
//}

char	**shift_down_paths(char **paths)
{
	char	*swap;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
		i++;
	swap = paths[0];
	while (--i)
	{
		tmp = paths[i - 1];
		paths[i - 1] = paths[i];
		paths[i] = tmp;
	}
	return (paths);
}

char	**absolute_path(char **paths, t_command *cmd)
{
	char	*temp;
	char	*new_path;
	int		i;

	new_path = ft_calloc(sizeof(char), ft_strlen(cmd->arguments[0]) + 1);
	if (!new_path)
		return (paths);
	i = 0;
	while (cmd->arguments[0][i] && (and_slash(&(cmd->arguments[0][i]))))
	{
		new_path[i] = cmd->arguments[0][i];
		i++;
	}
	paths = ft_addlinetomatrix(paths, new_path);
	ft_print_matrix(paths);
	temp = cmd->arguments[0];
	cmd->arguments[0] = ft_strtrim(cmd->arguments[0], new_path);
	free(temp);
	return (paths);
}

char	**add_current_path(char **paths, char *cwd, t_command *cmd)
{
	char	*tmp;
	size_t	i;

	i = 1;
	// if ./ or ../ add cwd to path and mantain the part behind (?)
	if (cmd->arguments[0][0] == '.' && cmd->arguments[0][1] == '/' && i++)
	{
		paths = ft_addlinetomatrix(paths, cwd);
		tmp = cmd->arguments[0];
		cmd->arguments[0] = ft_strtrim(cmd->arguments[0], "./");
		free(tmp);
	}
	//else if (cmd->arguments[0][0] == '.' && cmd->arguments[0][1] == '.' 
	//	&& cmd->arguments[0][2] == '/')
	//	path = remove_double_points(path, cmd);
	if (cmd->arguments[0][0] == '/' && cmd->arguments[0][1] && i++)
		paths = absolute_path(paths, cmd);
	else if (cmd->arguments[0][0] && i++)
		paths = ft_addlinetomatrix(paths, ft_strdup("/"));
	//free(cwd);
	if (i > 1)
		paths = shift_down_paths(paths);
	return (paths);
}

char	**ft_getpath(t_command *cmd)
{
	char	**path;
	char	*temp;
	char	cwd[MAXPATHLEN];

	temp = NULL;
	path = NULL;
	temp = exp_tkn("PATH", cmd->shell->env);
	path = ft_split(temp, ':');
	free(temp);
	if (!(getcwd(cwd, sizeof(cwd))))
		perror("getcwd() error");
	path = add_current_path(path, cwd, cmd);
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
	char			**path;
	char			*path_to_use;

	path = ft_getpath(cmd);
	pfn("%t -----------------------------");
	ft_print_matrix(path);
	ft_fixcommand(cmd);
	while (path[i++])
	{
		dir = opendir(path[i - 1]);
		entry = readdir(dir);
		while (entry)
		{
			if (ft_strcmp(entry->d_name, cmd->arguments[0]))
			{
				closedir(dir);
				path_to_use = ft_append(path[i - 1], cmd);
				ft_free_cmatrix(path);
				pfn("%1t %s", path_to_use);
				return (path_to_use);
			}
				entry = readdir(dir);
		}
		closedir(dir);
	}
	return (NULL);
}

/*
	***********************************************************
					FT_ADDLINETOMATRIX
	***********************************************************
	working
*/

char	**ft_addlinetomatrix(char **arr, char *line)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1 + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			ft_free_cmatrix(rtn);
			return (rtn);
		}
		i++;
	}
	rtn[i] = ft_strdup(line);
	i++;
	rtn[i] = NULL;
	ft_free_cmatrix(arr);
	return (rtn);
}
