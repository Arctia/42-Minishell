/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:22:37 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:22:38 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (pwd());
	else if (ft_strcmp(command, "env"))
		return (env(com));
	else if (ft_strcmp(command, "exit"))
		return (ms_exit(com));
	else if (ft_strcmp(command, "export"))
		return (ft_export(com->arguments, com->shell));
	return (-1);
}
