#include "../global.h"

void	ft_free_cmatrix(char **mtx)
{
	int	i;

	i = -1;
	if (mtx)
	{
		while (mtx[++i] && mtx[i][0])
		{
			//pfn("freeing mtx[%d] : p->%p s->%s", i, mtx[i], mtx[i]);
			free(mtx[i]);
		}
		free(mtx);
	}
}
//export [-fn] [name[=value] ...] or export -p
// NO FLAGS, NO OTIOINS, only export, export name, export name=value,
//ALSO a b c=6 d=
//SHOULD GIVE INSIDE THE ENV:
//***
//**
//*
//a
//b
//c="6"
//d=""
//
//BUT"c (space) =6" should prompt "export: '=6: not a valid identifier"
//

//copy env

//sort env

//read and add EACH new name(w/wout =value)

// OPPURE: fetch NAME while(env[i] ft_strncmp(env[i], NAME, ft_strlen(name)))
//se non lo ha trovato, if (ft_strncmp(env[i], NAME, ft_strlen(name)))
//sorta(alphab)e individua l'ultima posizione NON UTILE -->> i++;
//

int	alpha_cmp(char **str1, char **str2)
{
	char *tmp;

	tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
	// printf("CIAONE\n");
	return (0);
}
//come perdersi in un bicchiere d'acqua,
//ho fatto un casino, si puo fare molto piu'semplice
//i && k for mtrx lines, j for mtrx columns, n for size to compare
// if i < 0 sorta tutto altrimenti sorta finche'non arriva
int	ft_strcmp_better(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}


//se n < 0 sortala tutta, altrimenti sortala fino ad n
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
		while (i  < n -1 -k)
		{
			if (ft_strcmp_better(mtrx[i],mtrx[i + 1]) > 0)
				alpha_cmp(&mtrx[i], &mtrx[i + 1]);
			i++;
		}
		k++;
	}
}

//stac4$$0 di norma
void	export_aux(char **key_value, char **env_cpy)
{
	int	i;
	int	k;
	int	j;
	char **big_buff;

	j = 0;
	k = 0;
	i = 0;
	while (key_value[i++])
		while (env_cpy[k++])

	big_buff = malloc((i + k + 1) * sizeof (char *));
	i = 0;
	k = 0;
	while (big_buff[i])
	{
		while (!(((ft_strncmp(env_cpy[k++], key_value[j], 
				ft_strchr_len(key_value[j], '=')))) == 0))
		{
			big_buff[i] = ft_strdup(env_cpy[k]);
			j++;
		}
		big_buff[i++] = ft_strdup(key_value[j]);
		j++;
	}
	while (big_buff[i++] && key_value[j++])
		big_buff[i] = key_value[j];
	big_buff[i] = NULL;
}



//se key_value == NULL, sorta e stampa in ordine alpha gli argomenti
//altrimenti, verifica se key_value e'presente(con o senza '='), poi
//strjoinfree di ogni key_value -->> while (key_value[i] != ('\0'|| ))
// in fondo alla matrice
int	ft_export(char **key_value, t_hellmini shell)
{
	char	**env_cpy;
	int		i;
	int		k;
	int		n;

	i = -1;
	k = 0;
	n = -1;
	env_cpy = ft_arrdup(shell.env);
	if (key_value != NULL)
	{
		// alpha_sort(key_value);
		export_aux(key_value, env_cpy);
	}
	i = -1;
	alpha_sort(env_cpy);
	while (env_cpy[++i])
		printf("%s\n", env_cpy[i]);
	shell.env = env_cpy;
	ft_free_cmatrix(env_cpy);
	return (0);
}
// int	main()
// {
// 	t_hellmini shell;

// 	init_shell_env(shell.env, shell);
// 	init_shell(&shell);
// 	alpha_sort(shell.env);
// }
