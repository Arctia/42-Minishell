#include "../global.h"


// char	**ft_addlinetomatrix(char **arr, char *line)
// {
// 	char	**rtn;
// 	size_t	i;

// 	i = 0;
// 	while (arr[i] != NULL)
// 		i++;
// 	rtn = ft_calloc(sizeof(char *), i + 1 + 1);
// 	if (!rtn)
// 		return (NULL);
// 	i = 0;
// 	while (arr[i] != NULL)
// 	{
// 		rtn[i] = ft_strdup(arr[i]);
// 		if (rtn[i] == NULL)
// 		{
// 			ft_free_cmatrix(rtn);
// 			return (rtn);
// 		}
// 		i++;
// 	}
// 	rtn[i] = ft_strdup(line);
// 	i++;
// 	rtn[i] = NULL;
// 	return (rtn);
// }

//
//per key=value
char	*full_key_value(char *key_value)
{
	int		i;
	int		j;
	char	tmp[4095];
	char	*new_key_value;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(key_value))
	{
		if (i == ft_strchr_len(key_value, '='))
		{
			tmp[j++] = '=';
			//tmp[j++] = '"';
		}
		else if (key_value[i] == '"')
		{
			tmp[j++] = '\\';
			tmp[j++] = key_value[i];
		}
		else
			tmp[j++] = key_value[i];
		i++;
	}
	//tmp[j++] = '"';
	tmp[j++] = '\0';
	ft_printf("tmp: %s\n", tmp);
	new_key_value = ft_strdup(tmp);
	return (new_key_value);
}

//per key senza value, con o senza uguale
char	*check_key_value(char *key_value)
{
	char    *new_key_value;
	char    tmp[4095];
	int     i;
	int     z;
	int     full;

	i = -1;
	z = 0;
	full = ft_strchr_len(key_value, '=') + 1;
	while (i++ < (int)ft_strlen(key_value))
	{
		if (full <= 0)
		{  
			if (key_value[i] == '=' && i == (int)ft_strlen(key_value))
			{
				tmp[z] = key_value[i];
				tmp[z + 1] = '"';
				tmp[z + 2] = '"';
				tmp[z + 3] = '\0';
			}
			else
				tmp[z] = key_value[i]; 
		}
		else
		{
			while (key_value[i++])
				tmp[z] = key_value[i];
		}
		z++;
	}
	tmp[z++] = '\0';
	new_key_value = ft_strdup(tmp);
	return (new_key_value);
}

void	add_new_entries(char **key_value, char **big_buff, int	last)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	last++;
	while (big_buff[i++])
	{
		j = 0;
		while (key_value[j])
		{
			if (!ft_strcmp(big_buff[i], key_value[j]) && i == last)
			{
				big_buff[last] = key_value[j];
				last++;
			}
		}
		j++;
	}

}

// void	sort_export(char **key_value, char ** env_cpy, char **big_buff)
// {
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (env_cpy[k])
// 	{
// 		j = 0;
// 		while (key_value[j])
// 		{
// 			ft_printf("env %s key %s\n", env_cpy[k], key_value[j]); 
// 			if (ft_strncmp(key_value[j], env_cpy[k],ft_strchr_len(env_cpy[k], '=') - 1) == 0)
// 				{
// 					ft_printf("ilcazzochetipare\n");
// 					if (ft_strlen(key_value[j]) <= ft_strlen(env_cpy[k]))
// 						big_buff[i] = check_key_value(key_value[j]);
// 					else
// 						big_buff[i] = full_key_value(key_value[j]);
// 				}
// 			else
// 				big_buff[i] = ft_strdup(env_cpy[k]);
// 			i++;
// 			j++;
// 		}
// 		k++;
// 	}
// 	 write(1, "added existing\n", 16 );
// 	// add_new_entries(key_value, env_cpy, i);
// }


char	**sort_export(char **key_value, char ** env_cpy, char **big_buff)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	printf("enteringtheduungeon\n");

	while (env_cpy[++k])
		big_buff[i++] = ft_strdup(env_cpy[k]);

	while (key_value[++j])
	{
		k = -1;
		while (env_cpy[++k])
		{
			if (ft_strncmp(key_value[j], env_cpy[k],
				ft_strchr_len(env_cpy[k], '=') -1) != 0)
				{
					//big_buff[i++] = ft_strdup(env_cpy[k]);
					//printf("PORCODIOLADRO\n");
				}
			if (!env_cpy[k + 1] && ft_strchr_len(key_value[j], '=') == -1)
			{
				big_buff[i++] = check_key_value(key_value[j]);
				printf("MADONNAMAIALA\n");
			}
			else if (!env_cpy[k + 1])
			{
				big_buff[i++] = full_key_value(key_value[j]);
				printf("GESUAPPESO\n");
			}
		}
	}
	
	return (big_buff);
}