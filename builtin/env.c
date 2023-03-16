#include "../global.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

int	env(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->minishell->env[i])
	{
		ft_putendl_fd(cmd->minishell->env[i], 1);
		i++;
	}
	return (0);
}
