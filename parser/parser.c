
#include "./parser.h"
#define GRN "\033[1;32m"
#define WHITE "\033[0m"

/*##############################################################################
#	Set command name TO FIX for redirections add them if they're behind
############################################################################*/
static void	set_command_name(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->command = (char *) malloc(sizeof(char)
			* ft_strlen(cmd->tokens[0]) + 1);
	while (cmd->tokens[0][i++])
		cmd->command[i - 1] = cmd->tokens[0][i - 1];
	cmd->command[i - 1] = '\0';
}

static void	set_arguments(t_command *cmd, int args, int i)
{
	int	j;

	cmd->arguments = (char **) malloc(sizeof(char *) * args + 1);
	if (!(cmd->arguments))
		return ;
	i = 1;
	while (i < args)
	{
		if (cmd->tokens[i] != NULL && 0[cmd->tokens[i]] == '|')
			break ;
		cmd->arguments[i - 1] = ft_calloc(sizeof(char),
				ft_strlen(cmd->tokens[i]) + 1);
		if (!cmd->arguments[i - 1])
		{
			free(cmd->arguments);
			return ;
		}
		j = 0;
		while (cmd->tokens[i][j++])
			cmd->arguments[i - 1][j - 1] = cmd->tokens[i][j - 1];
		i++;
	}
	cmd->arguments[i - 1] = NULL;
	if (i == 1)
		cmd->arguments[0] = NULL;
}

/*##############################################################################
#	Splitter Functions
############################################################################*/
/* __ items in string ___________________?______________________________________
		. return number of items to be stored
		. single/double quotes TODO
_________________________________________!_________________________________ */
int	i_after_quote(char *str, int i, int *iw, int *in)
{
	char	c;

	c = str[i];
	if (*iw == 0 && str[i + 1] && str[i] != str[i + 1])
	{
		*iw = 1;
		*in = *in + 1;
	}
	i++;
	i = to_next_quote(str, i, c);
	return (i);
}

int	items_in_string(char *str)
{
	int	items_number;
	int	in_word;
	int	i;

	i = 0;
	in_word = 0;
	items_number = 0;
	while (str[i])
	{	
		if (ft_isquote(str[i]))
			i = i_after_quote(str, i, &in_word, &items_number);
		else if (ft_isnotspace(str[i]) && in_word == 0)
		{
			items_number++;
			in_word = 1;
		}
		else if (ft_isspace(str[i]))
			in_word = 0;
		i++;
	}
	return (items_number);
}

/* __ Replace string ____________________?______________________________________
		- cycle until space found
		- inner cycle for quote/s (do not consider inside different quote)
_________________________________________!_________________________________ */
void	write_word_expander(char *cnt, char *str)
{
	char	fchar;
	int		i;

	i = 0;
	fchar = str[0];
	while (ft_isnotspace(str[0]))
	{
		fchar = str[0];
		if ((fchar == '\'' || fchar == '\"') && str++[0])
		{
			while (str[0] && str[0] != fchar)
				cnt[i++] = str++[0];
		}
		else
			cnt[i++] = str++[0];
	}
	cnt[i] = '\0';
}

// consider quotes!
void	write_word_old(char *cnt, t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->str[0] && ft_isnotspace(cmd->str[0]))
	{
		cnt[i++] = cmd->str++[0];
	}
	cnt[i] = '\0';
}

void	write_word(char *cnt, t_command *cmd)
{
	int	i;
	int	t;
	int	c;

	i = 0;
	t = 0;
	c = 0;
	while (cmd->str[0])
	{
		if (ft_isquote(cmd->str[0]))
		{
			c = 0;
			t = to_next_quote(cmd->str, 1, cmd->str[0]);
			while (c++ <= t)
				cnt[i++] = cmd->str++[0];
		}
		else
			cnt[i++] = cmd->str++[0];
		if (ft_isspace(cmd->str[0]))
			break ;
	}
	cnt[i] = '\0';
}

void	write_redirection(t_command *cmd, char c1, char c2)
{
	int	red_n;

	red_n = 0;
	while (cmd->red_type[red_n] && cmd->red_type[red_n] != -1)
		red_n++;
	if (c2 && c2 == '<')
		cmd->red_type[red_n] = HERDOC;
	else if (c2 && c2 == '>')
		cmd->red_type[red_n] = REDAPP;
	else if (c1 == '<')
		cmd->red_type[red_n] = REDIN;
	else if (c1 == '>')
		cmd->red_type[red_n] = REDOUT;
	move_to_next_char(cmd);
	cmd->red[red_n] = ft_calloc(sizeof(char), ft_strlen(cmd->str) + 1);
	write_word(cmd->red[red_n], cmd);
}

void	fill_token(t_command *cmd, int *argc)
{
	cmd->tokens[*argc] = ft_calloc(sizeof(char), ft_strlen(cmd->str) + 1);
	if (!(cmd->tokens[*argc]))
		return ;
	write_word(cmd->tokens[*argc], cmd);
	if (cmd->tokens[*argc] != NULL && cmd->tokens[*argc][0] == '|')
	{
		cmd->shell->mc_pipes += 1;
		//cmd->tokens[*argc][0] = '\0';
	}
	*argc = *argc + 1;
}

void	before_write_word(t_command *cmd, int *argc, int *items)
{
	char	c;

	c = ft_isredirection(cmd->str[0]);
	if (c)
	{
		cmd->str++;
		if (ft_isredirection(cmd->str[0]) == c)
		{
			cmd->str++;
			write_redirection(cmd, c, c);
		}
		else
			write_redirection(cmd, c, 0);
		*items = *items - 2;
	}
	else
	{
		fill_token(cmd, argc);
	}
	move_to_next_char(cmd);
}

int	exit_quotes_if_it_is_one(char *str, int i)
{
	char	c;

	c = ft_isquote(str[i]);
	if (!c)
		return (i);
	i++;
	while (!(ft_isquote(str[i]) == c))
		i++;
	return (i);
}

int	red_in_string(t_command *cmd, char *str, int red_n)
{
	char c;
	int i;

	i = 0;
	c = 0;
	while (str[i])
	{
		i = exit_quotes_if_it_is_one(str, i);
		c = ft_isredirection(str[i]);
		if (c && str[i + 1] && ft_isredirection(str[i + 1]))
		{
			red_n += 1;
			i += 2;
		}
		else if (c)
		{
			red_n++;
			i += 1;
		}
		else
			i += 1;
	}
	cmd->red_type = ft_calloc(sizeof(int), red_n + 1);
	cmd->red = (char **) malloc(sizeof(char *) * red_n + 1);
	return (red_n);
}

/* __ split string ______________________?______________________________________
		. Count items to be store and allocate them
		. Allocate every single item
		. Write them
_________________________________________!_________________________________ */
int	split_string(t_command *cmd)
{
	char	*init;
	int		items;
	int		red_n;
	int		c;

	init = cmd->str;
	write(1, "ciaonez\n", 9);
	move_to_next_char(cmd);

	write(1, "le chars\n", 10);

	red_n = red_in_string(cmd, cmd->str, 0);
	ft_filliarrayto_n(cmd->red_type, EMPTY, red_n);

	items = items_in_string(cmd->str);
	write(1, "le items\n", 10);
	cmd->tokens = (char **) malloc(sizeof(char *) * items + 1);
	if (!(cmd->tokens))
		return (0);
	write(1, "strings malloc ok\n", 19);
	c = 0;
	while (cmd->str[0] != 0)
	{
		//write_from_quote_to_quote(cmd->tokens[c])
		before_write_word(cmd, &c, &items);
	}
	cmd->tokens[c] = NULL;
	cmd->str = init;
	return (items);
}

void	init_flags(t_command *cmd)
{
	int	i;

	i = 7;
	while (i >= 0)
		cmd->spc[i--] = 0;
}

void	set_operator_flags(t_command *cmd, char *s, int *m)
{
	if (s[*m] == '|')
		cmd->spc[PIPE] = 1;
	else if (s[*m] == '>' && s[*m + 1] && s[*m + 1] == '>')
	{
		cmd->spc[REDAPP] = 1;
		*m = *m + 1;
	}
	else if (s[*m] == '<' && s[*m + 1] && s[*m + 1] == '<')
	{
		cmd->spc[HERDOC] = 1;
		*m = *m + 1;
	}
	else if (s[*m] == '<')
		cmd->spc[REDIN] = 1;
	else if (s[*m] == '>')
		cmd->spc[REDOUT] = 1;
}

void	set_meta_flags(t_command *cmd,char c)
{
	if (c == '$')
		cmd->spc[CASH] = 1;
	else if (c == '\'' && cmd->spc[DQUOTE] == 1)
		cmd->spc[MQUOTE] = 1;
	else if (c == '"' && cmd->spc[SQUOTE] == 1)
		cmd->spc[MQUOTE] = 1;
	else if (c == '\'')
		cmd->spc[SQUOTE] = 1;
	else if (c == '"')
		cmd->spc[DQUOTE] = 1;
		
}

void	set_cmd_flags(t_command *cmd, int i)
{
	char	quote;
	int		q;

	q = 0;
	quote = 0;
	while (cmd->str[i])
	{
		set_meta_flags(cmd, cmd->str[i]);
		if (ft_isquote(cmd->str[i]) && q == 0)
		{
			quote = cmd->str[i];
			q = 1;
		}
		else if (q == 1 && ft_isquote(cmd->str[i]) == quote)
		{
			quote = 0;
			q = 0;
		}
		if (q == 0)
			set_operator_flags(cmd, cmd->str, &i);
		i++;
	}
}

/*##############################################################################
#	Tokenizer receives shell struct, cycles through all commands and
		fill their fields. Every command struct should have a
		str, which stores input with the operator at the end
############################################################################*/
void	print_arguments_and_flags(t_command *cmd)
{
	int	i;
	char *ar[] = {"PIPE", "SQUOTE", "DQUOTE", "MQUOTE",
			"REDIN ", "REDOUT", "REDAPP", "HERDOC", "CASH"};
	char *co[] = {" ", GRN"TRUE"WHITE};
	i = 0;
	pfn("%2t command: '%s'", cmd->command);
	while (cmd->arguments[i])
	{
		pfn("%2t arg[%d]: '%s'", i, cmd->arguments[i]);
		i++;
	}
	i = 0;
	pfn("%t -----------------------");
	while (i < 9)
	{
		if (cmd->spc[i])
			pfn("%t %-8s-->  %s", ar[(i) % 9], co[cmd->spc[i] % 2]);
		i++;
	}
	pfn("%t -----------------------");
	i = -1;
	while (cmd->red_type[++i] != 0)
		pfn("%t %d. %s -> %s", i, ar[cmd->red_type[i]], cmd->red[i]);
	pfn("%t -----------------------");
	pfn("%t shell pipes: %d", cmd->shell->mc_pipes);
}

int	parser(t_hellmini *sh)
{
	t_command	*cmd;
	int			args;

	sh->mc_pipes = 0;
	cmd = sh->current_cmd;
	while (cmd && cmd != NULL)
	{
		args = split_string(cmd);
		if (!args)
			return (FAIL);
		set_command_name(cmd);
		init_flags(cmd);
		set_cmd_flags(cmd, 0);
		set_arguments(cmd, args, 1);
		print_arguments_and_flags(cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (SUCCESS);
}

/*int	main(int argc, char **argv){
	t_hellmini *shell;
	t_command *cmd;
	char	*str = "echo -n 'debbing' |\0";

	shell = (t_hellmini *)malloc(sizeof(t_hellmini));
	cmd = (t_command *)malloc(sizeof(t_command));
	shell->current_cmd = cmd;
	cmd->str = argv[1];
	cmd->next = NULL;
	//printf("%s\n", cmd->str);
	int o = parser(shell);
	printf("SS: %d\n", o);
	return (0);
}*/