
#include "./parser.h"

/*##############################################################################
#	Set command name
############################################################################*/
static void	set_command_name(t_command *cmd)
{
	int	i;

	i = 0;
	if (!(cmd->arguments && cmd->arguments[0]))
	{
		cmd->spc[NOCMD] = 1;
		return ;
	}
	cmd->command = ft_calloc(sizeof(char), ft_strlen(cmd->arguments[0]) + 1);
	while (cmd->arguments[0][i++])
		cmd->command[i - 1] = cmd->arguments[0][i - 1];
	cmd->command[i - 1] = '\0';
}

static void	set_arguments(t_command *cmd, int args, int i)
{
	int	j;

	cmd->arguments = (char **) malloc(sizeof(char *) * (args + 1));
	if (!(cmd->arguments))
		return ;
	i = 0;
	while (i < args)
	{
		if (cmd->tokens[i] != NULL && 0[cmd->tokens[i]] == '|')
			break ;
		cmd->arguments[i] = ft_calloc(sizeof(char),
				ft_strlen(cmd->tokens[i]) + 1);
		if (!cmd->arguments[i])
			return (free(cmd->arguments));
		j = 0;
		while (cmd->tokens[i][j++])
			cmd->arguments[i][j - 1] = cmd->tokens[i][j - 1];
		i++;
	}
	cmd->arguments[i] = NULL;
	if (i == 0)
		cmd->arguments[0] = NULL;
}

static void	set_cmd_flags(t_command *cmd, int i)
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

/* __ split string ______________________?______________________________________
		. Count items to be store and allocate them
		. Allocate every single item
		. Write them
_________________________________________!_________________________________ */
static int	ps_split_string(t_command *cmd)
{
	char	*init;
	int		items;
	int		red_n;
	int		c;

	init = cmd->str;
	ps_move_to_next_char(cmd);
	red_n = red_in_string(cmd, cmd->str, 0);
	if (red_n > 0)
		ft_filliarrayto_n(cmd->red_type, EMPTY, red_n);
	items = items_in_string(cmd->str);
	pfn("items: %d", items);
	cmd->tokens = NULL;
	cmd->tokens = ft_calloc(sizeof(char *), items + 1);
	if (!(cmd->tokens))
		return (0);
	write(1, "strings malloc ok\n", 19);
	c = 0;
	while (cmd->str[0] != 0)
		before_write_word(cmd, &c, &items);
	cmd->tokens[c] = NULL;
	pfn("%t test 2");
	cmd->str = init;
	return (items);
}

/*##############################################################################
#	Tokenizer receives shell struct, cycles through all commands and
		fill their fields. Every command struct should have a
		str, which stores input with the operator at the end
############################################################################*/
static void	print_arguments_and_flags(t_command *cmd)
{
	int		i;
	char	*ar[] = {"PIPE", "SQUOTE", "DQUOTE", "MQUOTE",
			"REDIN ", "REDOUT", "REDAPP", "HERDOC", "CASH"};
	char	*co[] = {" ", GRN"TRUE"WHITE};

	i = 0;
	pfn("%2t command: '%s'", cmd->command);
	while (cmd->arguments && cmd->arguments[i])
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
	while (cmd->red && cmd->red_type[++i] != 0)
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
		args = ps_split_string(cmd);
		set_cmd_flags(cmd, 0);
		set_arguments(cmd, args, 1);
		set_command_name(cmd);
		print_arguments_and_flags(cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (SUCCESS);
}
