#include "executor.h"

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
	char	**arg;

	if (cmd->command && redirector(cmd) != -1)
		return ;
	if (cmd->command && ft_strchr(cmd->command, '/'))
		path = ft_strdup(cmd->command);
	else if (cmd->command)
		path = ft_findpath(cmd, 0);
	else
		return ;
	arg = cmd->arguments;
	pid = fork();
	if (!pid)
		execute_process(cmd->shell, path, arg);
	else if (pid < 0)
		perror("execv fork failed");
	else
	{
		waitpid(pid, status, WUNTRACED);
		while (!WIFEXITED(*status) && !WIFSIGNALED(*status))
			waitpid(pid, status, WUNTRACED);
	}
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
	// int		status;
	// t_command *cmd;

	// cmd = shell->current_cmd;
	pid = 111;
	while (cmd)
	{
		if (cmd->spc[DQUOTE] || cmd->spc[SQUOTE] || cmd->spc[MQUOTE] 
				|| cmd->spc[CASH] || cmd->spc[TILDE])
			expander(cmd);
		pfn("%3t -----------------------------------------------------------");
		pfn("%t running command: %s", cmd->str);
		if (cmd->spc[REDIN] || cmd->spc[REDOUT] || cmd->spc[REDAPP])
		{
			ft_redir(cmd);
			break;
		}
		// if (cmd->spc[HERDOC])
		// 	ft_heredoc(cmd);
		else if (cmd->next == NULL)	//simple command?
		{
			// if (ft_strcmp(cmd->command, builtin[i]))
			//if (ft_builtin(cmd->command))
			//	;
			//else
			ft_execv(cmd, pid, &(cmd->shell->exit_status));
		}
		else if (cmd->spc[PIPE])
		{ 
			ft_pipe(cmd);
			break ;
		}
		cmd = cmd->next;
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
