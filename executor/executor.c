#include "executor.h"
#include "../glob.h"

/*
	***********************************************************
					FT_EXECV
	***********************************************************
	working 
	l'ultimo else mi è un po' oscuro 
	we have to decide if do the fork in ft execve or in executor
*/
void	ft_execv(t_command *cmd, pid_t pid, int *status)
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
	signal(SIGINT, control_c_signal);
	waitpid(-1, status, 0);
	if (*status && get_ecode() != 130)
		set_ecode(127);
	free(path);
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
	pid_t	pid;
	int		std_cpy[2];

	std_cpy[0] = dup(STDIN_FILENO);
	std_cpy[1] = dup(STDOUT_FILENO);
	pid = 111;
	if (cmd->spc[PIPE])
		ft_pipe(cmd, std_cpy, pid);
	else if (cmd)
	{
		if (cmd->spc[DQUOTE] || cmd->spc[SQUOTE] || cmd->spc[MQUOTE]
			|| cmd->spc[CASH] || cmd->spc[TILDE])
			expander(cmd);
		pfn("%3t -----------------------------------------------------------");
		pfn("%t running command: %s", cmd->str);
		if (!cmd->spc[PIPE] && (cmd->spc[REDIN] || cmd->spc[REDOUT]
				|| cmd->spc[REDAPP] || cmd->spc[HERDOC]))
		{
			ft_redir(cmd, &std_cpy[0], &std_cpy[1]);
			return ;
		}
		ft_execv(cmd, pid, &(cmd->shell->exit_status));
	}
}
