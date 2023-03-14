#include "../global.h"

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
char **exp_(t_hellmini shell)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	char **new_env;
	new_env = ft_arrdup(shell.env);
	return (new_env);
}

void	alpha_cmp(char *str1, char *str2)
{
	char *tmp;

	tmp = str1;
	if ((unsigned char)*str1 > (unsigned char)*str2)
	{
		tmp = str1;
		str1 = str2;
		str2 = tmp;
		//printf("%s einz\n", str1);
	}
}

//come perdersi in un bicchiere d'acqua,
//ho fatto un casino, si puo fare molto piu'semplice
//i && k for mtrx lines, j for mtrx columns, n for size to compare
void	alpha_sort(char **mtrx)
{
	size_t	i;
	//int	j;
	size_t	k;
	int	n;

	i = 0;
	k = 1;
	n = 1;
	//j = ft_strlen;
	while (mtrx[i])
	{
		n = 1;
		k = i + 1;
		printf("N = %d\n", n);
		printf("i = %zu: %s\n", i, mtrx[i]);
		printf("k = %zu: %s\n", k, mtrx[k]);
		//write(1, "porcodio\n", 10);
		if (ft_strncmp(mtrx[i], mtrx[k], n))// mtrx[i][0] == mtrx[k][0]
		{
			while (((ft_strncmp(mtrx[i], mtrx[k], n) == 0) && mtrx[i] && mtrx[k]))
			{
				n++;
				write(1, "PPORCAMDONNA\n",14);
			}
			if(mtrx[i][n + 1] != mtrx[k][n + 1])
			{
				write(1, "PORCODIO\n", 10);
				i++;
			}
		}
		if (!ft_strncmp(mtrx[i], mtrx[k], n)
			&& mtrx[i][n + 1] != mtrx[k][n + 1])
			{
				alpha_cmp(mtrx[i], mtrx[k]);
				i++;
			}
		else
			i++;
	}
}
	// while ()
	// if ((unsigned char)mtrx[i][n] > (unsigned char)mtrx[k][n])
			// {
			// 	mtrx[k] = mtrx[i];
			// 	k++;
			// }
			// else if ((unsigned char)mtrx[i][n] < (unsigned char)mtrx[k][n])
			// {
			// 	mtrx[i] = mtrx[k];
			// 	k++;
			// }
			// printf("%s zwei\n", mtrx[k]);
int	ft_export(char **mtrx, char *str)
{
	(void)mtrx;
	(void)str;

	return (0);
}
// int	main()
// {
// 	t_hellmini shell;

// 	init_shell_env(shell.env, shell);
// 	init_shell(&shell);
// 	alpha_sort(shell.env);
// }
