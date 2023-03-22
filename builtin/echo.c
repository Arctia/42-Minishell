#include "./../global.h"

static int	skip_arguments(t_command *cmd, int	*flag)
{
	int	n;
	int	i;

	n = 1;
	while (cmd->arguments && cmd->arguments[n])
	{
		if (cmd->arguments[n][0] == '-')
		{
			i = 1;
			while (cmd->arguments[n][i] == 'n')
				i++;
			if (i > 1 && cmd->arguments[n][i] == '\0')
			{
				n++;
				*flag = 1;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (n);
}

int	echo(t_command *cmd)
{
	int		n_flag;
	int		n;
	int		i;

	n_flag = 0;
	n = skip_arguments(cmd, &n_flag);
	//while (cmd->arguments[++n] && !ft_strncmp(cmd->arguments[n], "-n", 3))
	//	n_flag = 1;
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
