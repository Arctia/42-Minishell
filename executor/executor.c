#include "executor.h"
#include "../glob.h"

/*
	***********************************************************
					FT_EXPANDER
	***********************************************************
	Before a node from t_simple_cmds is handled it is expanded.
	The expander takes variables, identified by $,
	and replaces them with their value from 
	the environment variables. Such that $USER becomes mgraaf,
	and $? is replaced with the exit code.

	Pay attention to export : export a = ls
	$a-> ls

	"" '' are alredy gestite from lexer/parser?
*/

char	*ft_expander(char *str, char **env)
{
	int i;
	int j;
	int k;
	char    *new_token;
	i = 0;
	j = 0;
	if (!str || !env || !ft_strlen(str))
		return(NULL);
	while (!((ft_strncmp(str, env[i], ft_strlen(str))) == 0))
		i++;
	while(env[i][j] != '=')
		j++;
	j++;
	new_token = (char *)malloc((ft_strlen(env[i]) + 2 - j));
	if (!new_token)
		return (NULL);
	k = 0;
	while (env[i][j])
		new_token[k++] = env[i][j++];
	new_token[k] = '\0';
	return (new_token);
}

/*
	***********************************************************
					FT_BUILTIN
	***********************************************************
	is not mine, is magic from madrid should be ok
	prototype:
	int	ft_namebultin(t_hellmini *shell)

int	(*ft_builtin(char *str))(t_hellmini *shell)
{
	static void	*builtins[7][2] = {
	{"echo", ft_echo},
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"export", ft_export},
	{"unset", ft_unset},
	{"env", ft_env},
	{"exit", ft_exit}
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
				return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}*/

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
	signal(SIGQUIT, control_c_signal);
	waitpid(0, status, 0);
	if (*status && get_ecode() != 130 && get_ecode() != 131)
		set_ecode(WIFEXITED(*status));
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
	pid_t	pid;

	pid = 111;
	if	(cmd->spc[PIPE])
			ft_pipe(cmd);
	else if (cmd)
	{
		if (cmd->spc[DQUOTE] || cmd->spc[SQUOTE] || cmd->spc[MQUOTE] 
				|| cmd->spc[CASH] || cmd->spc[TILDE])
			expander(cmd);
		if (cmd->command && cmd->command[0] == '\0' && shift_arguments(cmd, 0))
			return ;
		pfn("%3t -----------------------------------------------------------");
		pfn("%t running command: %s", cmd->str);
		if (cmd->spc[REDIN] || cmd->spc[REDOUT] || cmd->spc[REDAPP] || cmd->spc[HERDOC])
		{
			ft_redir(cmd);
			return ;
		}
		ft_execv(cmd, pid, &(cmd->shell->exit_status));
	}
}

/*
	***********************************************************
					FT_FIXCOMMAND
	***********************************************************
	hope working
	maybe generalize it if necessary
*/

void	ft_fixcommand(t_command *cmd)
{
	char	*temp;
	char	*tmp;

	if (ft_strncmp("./", cmd->arguments[0], 2) == 0)
	{
		tmp = cmd->arguments[0];
		temp = ft_strtrim(cmd->arguments[0], "./");
		cmd->arguments[0] = temp;
		free(tmp);
	}
}
