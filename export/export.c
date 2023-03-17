#include "global.h"

int	ms_cmdcmp(char **env, int s, int x)
{
	
}

void	ordered_env(char **env, int p, int c)
{
	char	*az;
	int		x;
	int		y;
	int		s;
	int		i;

	az = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	i = 0;
	x = 0;
	y = 0;
	while (env[i] != 0)
		i++;
	while (x < i - 1)
	{
		if(env[x] == az[p])
		{
			if (s == 0)
				s = x;
			else
				s = ms_cmdcmp(env, s, x);
		}
		x++;
	}

}

int add_env_line()

int export(t_command *com)
{
	if (!com->arguments)
	{

		ordered_env(t_command.shell.env, 0, 0);
	}
}