
#include "../global.h"

char    **ft_arrdup(char **arr)
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
}
