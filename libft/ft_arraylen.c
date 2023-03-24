
#include "libft.h"

size_t	ft_arrlen(int *array)
{
	size_t	i;

	i = 0;
	if (array)
	{
		while (array[i])
			i++;
	}
	return (i);
}
