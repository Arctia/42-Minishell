#include "../global.h"

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
			tmp[j++] = '=';
		else if (key_value[i] == '"')
		{
			tmp[j++] = key_value[i];
		}
		else
			tmp[j++] = key_value[i];
		i++;
	}
	tmp[j++] = '\0';
	ft_printf("tmp: %s\n", tmp);
	new_key_value = ft_strdup(tmp);
	return (new_key_value);
}

//per key senza value, con o senza uguale
// char	*check_key_value(char *key_value)
// {
// 	char	*new_key_value;
// 	char	tmp[4095];
// 	int		i;
// 	int		z;
// 	int		full;

// 	i = -1;
// 	z = 0;
// 	full = ft_strchr_len(key_value, '=') + 1;
// 	while (i++ < (int)ft_strlen(key_value))
// 	{
// 		if (full <= 0)
// 		{
// 			if (key_value[i] == '=' && i == (int)ft_strlen(key_value))
// 			{
// 				tmp[z] = key_value[i];
// 				tmp[z + 1] = '"';
// 				tmp[z + 2] = '"';
// 				tmp[z + 3] = '\0';
// 			}
// 			else
// 				tmp[z] = key_value[i];
// 		}
// 		else
// 		{
// 			while (key_value[i++])
// 				tmp[z] = key_value[i];
// 		}
// 		z++;
// 	}
// 	tmp[z++] = '\0';
// 	new_key_value = ft_strdup(tmp);
// 	return (new_key_value);
// }

char	*check_key_value(char *key_value)
{
	char	*new_key_value;
	char	tmp[4095];
	int		i;
	int		z;

	i = -1;
	z = 0;
	while (i++ < (int)ft_strlen(key_value))
	{
		if ((ft_strchr_len(key_value, '=') + 1) <= 0)
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
	ft_printf("%1t debug: %s", new_key_value);
	return (new_key_value);
}

void	add_new_entries(char **key_value, char **big_buff, int last)
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

char	**sort_export(char **key_value, char **env_cpy, char **big_buff)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	while (env_cpy[++k])
		big_buff[i++] = ft_strdup(env_cpy[k]);
	while (key_value[++j])
	{
		k = -1;
		while (env_cpy[++k])
		{
			if (!env_cpy[k + 1] && ft_strchr_len(key_value[j], '=') == -1)
				big_buff[i++] = check_key_value(key_value[j]);
			else if (!(env_cpy[k + 1]))
				big_buff[i++] = full_key_value(key_value[j]);
		}
	}
	return (big_buff);
}
