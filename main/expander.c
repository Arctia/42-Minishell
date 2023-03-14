
#include "../global.h"
// Constant declarations
//# define NAME_MAX 255
//# define PATH_MAX 1024

//keeps reading the env until it finds the desired $VAR, then
//mallocs and replaces $VAR with it's expansion(aka the string after '=')
/*char *exp_tkn(char *str, char **env)
{
	int	i;
	int	j;
	int	k;
	char	*new_token;

	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return(NULL);
	while (!((ft_strncmp(str, env[i], ft_strlen(str))) == 0))
		i++;
	while(env[i][j] != '=')
		j++;
	j++;
	new_token = (char *)malloc((ft_strlen(env[i]) + 2 - j));
	if (!new_token)
		return (NULL);
	k = 0;
	while(env[i][j])
		new_token[k++] = env[i][j++];
	new_token[k] = '\0';
	return (new_token);
}*/

void    free_arr(char **split_arr)
{
    int i;
    i = 0;
    while (split_arr[i])
    {
        free(split_arr[i]);
        i++;
    }
    free(split_arr);
}

/*char    **ft_arrdup(char **arr)
{
    char    **rtn;
    size_t  i;

	i = 0;
    //ft_putstr_fd("Dioboia",1);
	while (arr[i] != NULL)
        i++;
    rtn = ft_calloc(sizeof(char *), i + 1);
    if (!rtn)
        return (NULL);
    i = 0;
	//ft_putstr_fd("Dioboia2",1);
    while (arr[i] != NULL)
    {
        rtn[i] = ft_strdup(arr[i]);
        if (rtn[i] == NULL)
        {
            free_arr(rtn);
            return (rtn);
        }
       i++;
    }
	//ft_putstr_fd("Dioboia3",1);
    rtn[i] = NULL;
    return (rtn);
}*/
// int test_main(char **envp)
// {
//     t_hellmini seashell;
//     seashell.env = ft_arrdup(envp);
//     // ft_getpath(&seashell);
//     exp_tkn("$user", seashell.env);
//     return 0;
// }
