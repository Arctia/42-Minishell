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

	tmp = cmd->command;
	ret = malloc(sizeof(char ) * (ft_strlen(path)
				+ ft_strlen(cmd->command)) + 2);
	if (!ret)
		return (NULL);
	retaux = ret;
	while (*path)
		*ret++ = *path++;
	*ret++ = '/';
	while (*cmd->command)
		*ret++ = *cmd->command++;
	*ret++ = '\0';
	cmd->command = tmp;
	return (retaux);
}

/*
	***********************************************************
					FT_GETPATH
	***********************************************************
	working
	path da freeare
*/

char	**ft_getpath(t_command *cmd, int i)
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
			if (ft_strncmp("./", cmd->command, 2) == 0)
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
	char			*temp;

	path = ft_getpath(cmd, 0);
	ft_fixcommand(cmd);
	while (path[i])
	{

		dir = opendir(path[i]);
		entry = readdir(dir);

		while (entry)
		{
			if (ft_strcmp(entry->d_name, cmd->command))
			{

				closedir(dir);

				temp = ft_append(path[i], cmd);
				ft_free_cmatrix(path);
				return (temp);
			}
				entry = readdir(dir);

		}

		closedir(dir);
		i++;
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
	return (rtn);
}
