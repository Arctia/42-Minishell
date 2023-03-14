
#include "./../global.h"

static void	free_things_inside_command(t_command *cmd)
{
	ft_free_cmatrix(cmd->arguments);
	ft_free_cmatrix(cmd->tokens);
	ft_free_ptr(cmd->red_type);
	ft_free_ptr(cmd->command);
	ft_free_cmatrix(cmd->red);
	ft_free_ptr(cmd->red);
	ft_free_ptr(cmd->str);
	free(cmd);
}

void	free_commands(t_hellmini *shell)
{
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

/* env may need to be modified, 
	to do so we need to do an allocated
	copy of it */
void	free_shell(t_hellmini *shell)
{
	//pfn("%t entering shell free after execut fail");
	if (shell->input)
		free(shell->input);
	//pfn("%t free commands");
	free_commands(shell);

	//pfn("%t env not freable...");
	/*int i = 0;
	{
		while(shell->env[i])
		{
			//pfn("li %i %s", i, shell->env[i]);
			free(shell->env[i]);
			i++;
		}
	}
	free(shell->env);*/
	//pfn("%t free shell, wrong size, env to blame");
	free(shell);
}
