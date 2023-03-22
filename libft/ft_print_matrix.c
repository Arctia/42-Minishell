#include "libft.h"

void	ft_print_matrix(char **mtx)
{
	int	i;

	i = 0;
	if (mtx)
	{
		while (mtx[i])
		{
			ft_printf("element[%d]: %s\n", i, mtx[i]);
			i++;
		}
	}
}
