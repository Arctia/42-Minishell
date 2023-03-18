
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
	while (i < 11)
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

static void	init_shell_env(t_hellmini *shell, char **original_env)
{
	char	*sh_lvl;
	char	*itoa;
	int		i;

	shell->env = ft_arrdup(original_env);
	if (!shell->env)
	{
		write(1, "Error! Not enough memory to set env\n", 36);
		free(shell);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (original_env[i])
	{
		if (!ft_strncmp(original_env[i], "SHLVL=", 6))
		{
			sh_lvl = ft_strtrim(original_env[i], "SHLVL=");
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
	g_error_code = ft_calloc(sizeof(int), 0);
	shell->env = NULL;
	shell->input = NULL;
	shell->mc_pipes = 0;
	shell->mc_quotes = 0;
	shell->mc_wquotes = 0;
	shell->exit_status = 0;
	shell->current_cmd = NULL;
	init_shell_env(shell, env);
}
