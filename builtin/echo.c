#include "./../global.h"

int	echo(t_command *cmd)
{
	int		n_flag;
	int		n;
	int		i;

	n_flag = 0;
	n = 0;
	while (cmd->arguments[++n] && !ft_strncmp(cmd->arguments[n], "-n", 3))
		n_flag = 1;
	while (cmd->arguments[n])
	{
		if (cmd->arguments[n + 1])
		{
			ft_printf("%s", cmd->arguments[n++]);
			write(1, " ", 1);
		}
		else
			ft_printf("%s", cmd->arguments[n++]);
	}
	if (!n_flag)
		write(1, "\n", 1);
	cmd->shell->exit_status = 0;
	return (cmd->shell->exit_status);
}
