#include "./lexer.h"

//makes sure no quotes are not closed
int	check_closures(char *line, int i)
{
	char	quote;

	while (line[i] != 0)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] != 0 && line[i] != quote)
				i++;
			if (line[i] == 0)
				return (quote);
		}
		i++;
	}
	return (0);
}

//searches and split following commands from the line on the next command 
// argument
void	lexer_default(t_hellmini *shell, t_command *cmd, int not_new, int i)
{
	t_command	*tmp;
	char		*line;

	line = shell->input;
	while (1)
	{
		if (cmd == NULL)
		{
			cmd = init_command(shell);
			if (!cmd)
				return ;
			tmp->next = cmd;
			cmd->prev = tmp;
		}
		cmd->str = split_operator(line, &i, not_new++);
		tmp = cmd;
		cmd = NULL;
		if (line[i] == '\0')
			break ;
		i++;
	}
}

void	print_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	tmp = cmd;
	i = 0;
	while (tmp && tmp != NULL)
	{
		pfn("%d. %s", i, tmp->str);
		tmp = tmp->next;
		i++;
	}
}

int	ms_isoperator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

//main function and of the lexer process, it initializes the struct,
// checks unclosed quotes.
int	lexer_init(t_hellmini *shell)
{
	char		*line;
	int			exit_status;
	int			i;

	line = shell->input;
	line[ft_strlen(line)] = '\0';
	i = 0;
	exit_status = check_syntax(line, i);
	if (exit_status)
	{
		shell->exit_status = exit_status;
		return (exit_status);
	}
	shell->current_cmd = init_command(shell);
	if (!(shell->current_cmd))
		return (-1);
	lexer_default(shell, shell->current_cmd, 0, 0);
	print_commands(shell->current_cmd);
	return (0);
}
