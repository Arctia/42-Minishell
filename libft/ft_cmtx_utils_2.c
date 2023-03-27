#include "libft.h"

// fill array with val
void	ft_cmtx_fill(char **mtx, char *val)
{
	int	i;

	if (!val)
		return ;
	i = 0;
	while (mtx[i])
	{
		ft_free_ptr(mtx[i]);
		mtx[i] = ft_strdup(val);
		i++;
	}
	ft_free_ptr(val);
}

// return -1 if not found, else index of val
int	ft_cmtx_includes(char **mtx, char *val)
{
	int	i;

	if (!val)
		return (-1);
	i = 0;
	while (mtx[i])
	{
		if (ft_strcmp(mtx[i], val))
			return (i);
	}
	return (-1);
}

void	ft_cmtx_del_at(char **mtx, int id)
{
	int	i;

	if ((int) ft_cmtxlen(mtx) < id)
		return ;
	i = 0;
	while (mtx[i] && i != id)
		i++;
	ft_free_ptr(mtx[i++]);
	mtx[i - 1] = NULL;
	while (mtx[i])
	{
		mtx[i - 1] = mtx[i];
		mtx[i] = NULL;
	}
}
