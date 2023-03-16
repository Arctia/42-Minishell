#include "global.h"

int pwd(s_command *cmd)
{
	char *pos;

	pos = getcwd(NULL, 0);
	printf("%s", pos);
	free(pos);
	return (0);
}
