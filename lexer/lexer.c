#include "./../global.h"

t_command	*init_command(t_hellmini *shell)
{
	t_command	*cmd;
	int	i;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->str = NULL;
	cmd->tokens = NULL;
	i = 0;
	while (i < 9)
		cmd->spc[i++] = 0;
	cmd->command = NULL;
	cmd->flags = NULL;
	cmd->arguments = NULL;
	cmd->red_type = NULL;
	cmd->red = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->ret = 0;
	cmd->shell = shell;
	return (cmd);
}

void	kalirio()
{
	static int	i = 0;

	if (i == 0)
	{
		//printf("salve signore, è un piacere lavorare con lei\n");
		i++;
	}
	else
	{
		//printf("mio signore, il cammino fino a qui è assicurato, buona continuazione\n");
	}
}

/*int	ft_strlen(char *str)
{
	int i = 0;

	while(str[i])
		str[i++];
	return (i);
}

int	ft_isspace(int c)
{
	if (9 <= c && c <= 13 || c == 32)
		return (1);
	return (0);
}*/

//makes sure no quotes are not closed
int check_closures(char *line, int i)
{
	char	quote;
	//pfn("augusto: meow, la linea è: %s, i è:%d\n", line, i);
	while (line[i] != 0)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] != 0 && line[i] != quote)
				i++;
			if (line[i] == 0)
				return (-1);
		}
		i++;
	}
	//write(1, "\na\n", 3);
	return (0);
}

//searches and split following commands from the line on the next command argument
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
	t_command *tmp;
	int	i;

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

int	check_operator(char *line, int i)
{
	int	flag;

	flag = 0;
	while (ms_isoperator(line[i]) || ft_isspace(line[i]))
	{	
		if (!line[i + 1])
			return (-1);
		if (ms_isoperator(line[i]) == 1)
		{
			if (ms_isoperator(line[i + 1]) && line[i + 1] == '|')
				return (-1);
			else if (ms_isoperator(line[i + 1]) && line[i + 1] != line[i])
				return (-1);
			else if (ms_isoperator(line[i + 1]) && ms_isoperator(line[i + 2]))
				return (-1); 
			else if (ms_isoperator(line[i] == 1) && flag == 1)
				return (-1);
		}
		else if (ft_isspace(line[i]) == 1)
			flag = 1;
		i++;
	}
	return (0);
}

int	check_syntax(char *line, int i)
{
	//printf("cc=%d\n", check_closures(line, i));
	if (check_closures(line, i) != 0)
	{
		write(1, "?", 1);
		return (-1);
	}
	kalirio();
	//write(1, "meow", 4);
	while(line[i] != 0)
	{
		if (ms_isoperator(line[i]) == 1)
		{
			if (check_operator(line, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

//main function and of the lexer process, it initializes the struct, checks unclosed quotes.
int lexer_init(t_hellmini *shell)
{
	char		*line;
	int			i;

	line = shell->input;
	line[ft_strlen(line)] = '\0';
	i = 0;
	if (check_syntax(line, i) != 0)
	{
		lexer_error("bad syntax.");
		return (-1);
	}
	shell->current_cmd = init_command(shell);
	if (!(shell->current_cmd))
		return (-1);
	lexer_default(shell, shell->current_cmd, 0, 0);
	//printf("%s", shell->current_cmd->str);
	
	print_commands(shell->current_cmd);
	
	return (0);
}

//testing main, remove after testing
/*int main(int argc, char **argv)
{
	t_hellmini shell;
	int	i;

	i = 0;
	shell.input = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	while (i < ft_strlen(argv[1]))
	{
		shell.input[i] = argv[1][i];
		i++;
	}
	shell.input[i] = '\0';

	kalirio();
	lexer_init(&shell);
	
	return (0);
}*/
