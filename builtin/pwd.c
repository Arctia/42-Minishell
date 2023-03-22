#include "../global.h"

int	pwd(void)
{
	char	*pos;

	pos = getcwd(NULL, 0);
	ft_printf("%s\n", pos);
	free(pos);
	return (0);
}
