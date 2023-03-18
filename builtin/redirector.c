#include "./../global.h"

int	redirector(t_command *com)
{
	char	*command;

	command = com->command;
	if (ft_strcmp(command, "unset"))
		return (unset(com));
	else if (ft_strcmp(command, "cd"))
		return (cd(com));
	else if (ft_strcmp(command, "echo"))
		return (echo(com));
	else if (ft_strcmp(command, "pwd"))
		return (pwd(com));
	else if (ft_strcmp(command, "env"))
		return (env(com));
	else if (ft_strcmp(command, "exit"))
		ms_exit(com);
	/*else if (ft_strcmp(command, "export"))
		return (export(com));*/ 
	return (-1);
}
