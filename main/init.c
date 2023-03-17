
#include "../global.h"

t_command	*init_command(t_hellmini *shell)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->str = NULL;
	i = 0;
	while (i < 10)
		cmd->spc[i++] = 0;
	cmd->arguments = NULL;
	cmd->red_type = NULL;
	cmd->command = NULL;
	cmd->tokens = NULL;
	cmd->shell = shell;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->red = NULL;
	cmd->ret = 0;
	return (cmd);
}

static void	init_shell_env(char **or_env, t_hellmini *shell)
{
	char	*sh_lvl;
	char	*itoa;
	int		i;

	shell->env = ft_arrdup(or_env);
	if (!shell->env)
	{
		write(1, "Error!Not enough memory to set env\n", 36);
		free(shell);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (or_env[i])
	{
		if (!ft_strncmp(or_env[i], "SHLVL=", 6))
		{
			sh_lvl = ft_strtrim(or_env[i], "SHLVL=");
			itoa = ft_itoa(ft_atoi(sh_lvl) + 1);
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("SHLVL=", itoa);
			free(itoa);
			free(sh_lvl);
		}
		i++;
	}
}

void	init_shell(t_hellmini *shell, char **env)
{
	shell->env = NULL;
	shell->input = NULL;
	shell->mc_pipes = 0;
	shell->mc_quotes = 0;
	shell->mc_wquotes = 0;
	shell->exit_status = 0;
	shell->current_cmd = NULL;
	init_shell_env(env, shell);
}
