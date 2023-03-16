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
					FT_FINDPATH
	***********************************************************
	working
	la i passata è una porcata ma su due piedi era la cosa piu''
	facile per essere a norma e non avere leak
*/

size_t	ft_matrix_size(char	**mtx)
{
	size_t	i;

	i = 0;
	if (mtx)
	{
		while (mtx[i])
			i++;
	}
	return (i);
}

char	*ft_findpath(t_command *cmd, int i)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**paths;
	char			*path_to_use;

	paths = ft_getpath_old(cmd, 0);
	ft_fixcommand(cmd);
	while (paths[i++])
	{
		dir = opendir(paths[i - 1]);
		entry = readdir(dir);
		while (entry)
		{
			if (ft_strcmp(entry->d_name, cmd->arguments[0]))
			{
				closedir(dir);
				path_to_use = ft_append(paths[i - 1], cmd);
				ft_free_cmatrix(paths);
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
