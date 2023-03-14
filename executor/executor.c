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

void	ft_execv(t_hellmini *shell, pid_t pid)
{
	//char	*path;
	char	**arg;
	//int		status;
	int	tmp_index;
	(void)pid;
	tmp_index = 0;
	write(1, "ppath\n", 7);
	//path = ft_findpath(shell, 0);
	//ft_printf("path:%s\n",path);
	write(1, "aarg\n", 5);
	arg = ft_listtomatrix(shell);
	while (arg)
	{
		printf("%s\n", arg[tmp_index]);
		tmp_index++;
	}
	// pid = fork();
	// if (!pid)
	// {
	// 	printf("PID= %d\n", pid);
	// 	if (execve(path, arg, shell->env) == -1)
	// 	{
	// 		perror("execv execution failed");
	// 		free_shell(shell);
	// 		exit(1);
	// 	}
	// }
	// else if (pid < 0)
	// 	perror("execv fork failed");
	// else
	// {
		// waitpid(pid, &status, WUNTRACED);
		// while (!WIFEXITED(status) && !WIFSIGNALED(status))
			// waitpid(pid, &status, WUNTRACED);
	// }
	write(1, "voila\n", 6);
	ft_free_cmatrix(arg);
	write(1, "lematrix\n",10);
	// free(path);
	// exit(EXIT_FAILURE);
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
void	ft_executor(t_hellmini *shell)
{
	pid_t	pid;
	t_command *cmd;

	cmd = shell->current_cmd;
	pid = 111;
	while (cmd)
	{
		if (cmd->spc[DQUOTE] || cmd->spc[CASH] || cmd->spc[MQUOTE])
			the_expanse(shell->current_cmd);
		return ;
		if (cmd->next == NULL)	//simple command?
		{
			// if (ft_strcmp(cmd->command, builtin[i]))
			//if (ft_builtin(cmd->command))
			//	;
			//else
			ft_execv(shell, pid);
		}
		else if (cmd->spc[REDIN])
			ft_less(shell);
		else if (cmd->spc[REDOUT])
			ft_redir(shell);
		else if (cmd->spc[REDAPP])
			ft_moremore(shell);
		else if (cmd->spc[HERDOC])
			ft_heredoc(shell);
		else if (cmd->spc[PIPE])
		{
			ft_pipe(shell);
			// while (waitpid(0, &status ,0))
			// 	;//? not sure if here or in ft_executor with a while loop
		}
		// ft_execv(shell, pid); //see function comment maybe every single exceptio call his own ft_sexecv
		// if (cmd->next)
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

void	ft_fixcommand(t_hellmini *shell)
{
	char	*temp;
	char	*tmp;

	if (ft_strncmp("./", shell->current_cmd->command, 2) == 0)
	{
		tmp = shell->current_cmd->command;
		temp = ft_strtrim(shell->current_cmd->command, "./");
		shell->current_cmd->command = temp;
		free(tmp);
	}
}
