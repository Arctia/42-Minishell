#include "../global.h"

int	alpha_cmp(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
	return (0);
}

void	alpha_sort(char **mtrx)
{
	int	i;
	int	n;
	int	k;

	k = 0;
	n = 0;
	while (mtrx[n])
		n++;
	while (k < n)
	{
		i = 0;
		while (i < n - 1 - k)
		{
			if (ft_strcmp_better(mtrx[i], mtrx[i + 1]) > 0)
				alpha_cmp(&mtrx[i], &mtrx[i + 1]);
			i++;
		}
		k++;
	}
}

//stac4$$0 di norma
char	**export_aux(char **key_value, char **env_cpy)
{
	int		i;
	int		k;
	int		j;
	char	**big_buff;

	j = 0;
	k = 0;
	i = 0;
	while (key_value[i++])
		;
	while (env_cpy[k++])
		;
	big_buff = ft_calloc(sizeof(char *), i + k + 1);
	big_buff = sort_export(key_value, env_cpy, big_buff);
	write(1, "terminating\n", 13);
	i = 0;
	while (big_buff[i])
		i++;
	big_buff[i] = NULL;
	env_cpy = big_buff;
	return (env_cpy);
}

//se key_value == NULL, sorta e stampa in ordine alpha gli argomenti
//altrimenti, verifica se key_value e'presente(con o senza '='), poi
//strjoinfree di ogni key_value -->> while (key_value[i] != ('\0'|| ))
// in fondo alla matrice
int	ft_export(char **key_value, t_hellmini *shell)
{
	char	**env_cpy;
	int		i;
	int		k;

	k = 0;
	env_cpy = ft_arrdup(shell->env);
	if (key_value && key_value[1])
		env_cpy = export_aux(key_value, shell->env);
	else
	{
		alpha_sort(env_cpy);
		if (key_value[1] == NULL)
		{
			i = -1;
			while (env_cpy[++i]
					&& (!(env_cpy[i][0] == '_' && env_cpy[i][1] == '=')))
			{
				write(1, "declare -x ", 11);
				print_env_vars(env_cpy[i]);
			}
		}
	}
	ft_free_cmatrix(shell->env);
	shell->env = env_cpy;
	return (0);
}
