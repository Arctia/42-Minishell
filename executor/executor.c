/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:55:29 by mmariani          #+#    #+#             */
/*   Updated: 2023/03/22 23:55:32 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../glob.h"

static void	set_signals(void)
{
	signal(SIGINT, control_c_signal);
	signal(SIGQUIT, control_c_signal);
}

/*
	***********************************************************
					FT_EXECV
	***********************************************************
	working 
	l'ultimo else mi è un po' oscuro 
	we have to decide if do the fork in ft execve or in executor
*/

void	ft_execv(t_command *cmd, int *status)
{
	char	*path;
	int		ecode;

	if (cmd->command)
		ecode = redirector(cmd);
	if (cmd->command && ecode != -1)
	{
		set_ecode(ecode);
		return ;
	}
	if (cmd->command && ft_strchr(cmd->command, '/'))
		path = ft_strdup(cmd->command);
	else if (cmd->command)
		path = ft_findpath(cmd, 0);
	else
		return ;
	if (!fork())
		execute_process(cmd->shell, path, cmd->arguments);
	set_ecode(0);
	set_signals();
	waitpid(0, status, 0);
	if (*status && get_ecode() != 130
		&& get_ecode() != 131 && WIFEXITED(*status))
		set_ecode(WEXITSTATUS(*status));
	free(path);
}

int	shift_arguments(t_command *cmd, int i)
{
	while (i < cmd->args_number)
	{
		if (cmd->arguments[i] && !cmd->arguments[i][0]
				&& cmd->arguments[i + 1] && cmd->arguments[i + 1][0])
		{
			cmd->arguments[i] = cmd->arguments[i + 1];
			cmd->arguments[i + 1] = NULL;
			shift_arguments(cmd, 0);
		}
		i++;
	}
	if (!cmd->arguments || !cmd->arguments[0] || (!cmd->arguments[0][0]))
		return (1);
	free(cmd->command);
	cmd->command = ft_strdup(cmd->arguments[0]);
	return (0);
}

/*
	***********************************************************
					FT_EXECUTOR					
	***********************************************************
	the name is parser because it come from Parser
	
	i've to find the rgiht way to execute all command my if is
	good only for simple command
	

	maybe i need fd_in and fd_out in the command struct to swap 
	fd between pipe or maybe not

*/

void	ft_executor(t_command *cmd)
{
	int		std_cpy[2];

	std_cpy[0] = dup(STDIN_FILENO);
	std_cpy[1] = dup(STDOUT_FILENO);
	if (cmd->spc[PIPE])
		ft_pipe(cmd, std_cpy, 118, -1);
	else if (cmd)
	{
		if (cmd->spc[DQUOTE] || cmd->spc[SQUOTE] || cmd->spc[MQUOTE]
			|| cmd->spc[CASH] || cmd->spc[TILDE])
			expander(cmd);
		if (cmd->command && cmd->command[0] == '\0' && shift_arguments(cmd, 0))
			return ;
		if (!cmd->spc[PIPE] && (cmd->spc[REDIN] || cmd->spc[REDOUT]
				|| cmd->spc[REDAPP] || cmd->spc[HERDOC]))
		{
			ft_redir(cmd, &std_cpy[0], &std_cpy[1]);
			return ;
		}
		ft_execv(cmd, &(cmd->shell->exit_status));
	}
}
