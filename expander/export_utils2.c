#include "../global.h"



int	ft_strchr_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (i >= (int) ft_strlen(str))
		return (-1);
	return (i);
}