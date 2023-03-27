#include "libft.h"

// delete last element
void	ft_cmtx_pop(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		i++;
	ft_free_ptr(mtx[i - 1]);
	mtx[i - 1] = NULL;
}

// remove first element
void	ft_cmtx_shift(char **mtx)
{
	int	i;

	i = 1;
	ft_free_ptr(mtx[0]);
	mtx[0] = NULL;
	while (mtx[i])
	{
		mtx[i - 1] = mtx[i];
		mtx[i] = NULL;
		i++;
	}
}

// add element
void	ft_cmtx_append(char **old_mtx, char *new_str)
{
	int		old_len;
	char	**mtx;
	int		i;

	i = -1;
	old_len = (int) ft_cmtxlen(old_mtx);
	mtx = ft_calloc(sizeof(char *), old_len + 2);
	if (!mtx)
		return ;
	while (++i < old_len)
	{
		mtx[i] = old_mtx[i];
		old_mtx[i] = NULL;
	}
	mtx[i] = new_str;
	ft_free_cmatrix(old_mtx);
	old_mtx = mtx;
}

// insert new_value at the beginning
void	ft_cmtx_unshift(char **old_mtx, char *new_value)
{
	char	**mtx;
	int		i;

	mtx = ft_calloc(sizeof(char *), ft_cmtxlen(old_mtx) + 2);
	if (!mtx)
		return ;
	i = 0;
	mtx[0] = new_value;
	while (old_mtx[i])
	{
		mtx[i + 1] = old_mtx[i];
		old_mtx[i] = NULL;
		i++;
	}
	ft_free_ptr(old_mtx);
	old_mtx = mtx;
}

// reverse the array
void	ft_cmtx_reverse(char **old_mtx)
{
	char	**mtx;
	int		i;
	int		x;

	x = ft_cmtxlen(old_mtx);
	mtx = ft_calloc(sizeof(char *), x + 1);
	if (!mtx)
		return ;
	i = 0;
	while (x > 0)
	{
		mtx[i] = old_mtx[x];
		old_mtx[x] = NULL;
		i++;
		x--;
	}
	ft_free_ptr(old_mtx);
	old_mtx = mtx;
}
