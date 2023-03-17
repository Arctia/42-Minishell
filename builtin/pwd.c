#include "../global.h"

int pwd(t_command *cmd)
{
	char *pos;

	pos = getcwd(NULL, 0);
	ft_printf("%s\n", pos);
	free(pos);
	return (0);
}
