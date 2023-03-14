
#include "./../global.h"

static void	free_things_inside_command(t_command *cmd)
{
	int	i;

	//pfn("%3t free str");
	if (cmd->str != NULL)
		free(cmd->str);
	//pfn("%3t free command %p	%s", cmd->command, cmd->command);
	if (cmd->command != NULL)
		free(cmd->command);
	i = 0;
	//pfn("%3t free tokens");
	if (cmd->tokens != NULL)
	{
		while (cmd->tokens[i])
			free(cmd->tokens[i++]);
		free(cmd->tokens);
	}
	i = 0;
	//pfn("%3t free arguments");
	if (cmd->arguments != NULL)
	{
		while (cmd->arguments[i])
				free(cmd->arguments[i++]);
		free(cmd->arguments);
	}
	//pfn("%3t free self");
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
