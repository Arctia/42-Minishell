
#include "./../global.h"

static void	free_things_inside_command(t_command *cmd)
{
	return;
	//pfn("here i am 2");
	ft_free_cmatrix(cmd->arguments);
	ft_free_cmatrix(cmd->tokens);
	ft_free_ptr(cmd->red_type);
	//pfn("here i am 5");
	ft_free_ptr(cmd->command);
	ft_free_cmatrix(cmd->red);
	//pfn("here i am 7");
	ft_free_ptr(cmd->str);
	ft_free_ptr(cmd);
}

void	free_commands(t_hellmini *shell)
{
	return;
	t_command	*cmd;
	t_command	*nxt;

	cmd = shell->current_cmd;
	nxt = NULL;
	while (cmd)
	{
		nxt = cmd->next;
		free_things_inside_command(cmd);
		cmd = nxt;
	}
	shell->current_cmd = NULL;
}

void	free_shell(t_hellmini *shell)
{
	return;
	if (shell->input)
		free(shell->input);
	ft_free_cmatrix(shell->env);
	free_commands(shell);
	free(shell);
}
