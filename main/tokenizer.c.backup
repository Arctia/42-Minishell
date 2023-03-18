
#include "../global.h"
//From Bash Reference Manual:
//" '’’ preserves the literal value of each character within the quotes.
//A single quote may not occur between single quotes, even when preceded by a backslash.
// ‘ " ’ preserves the literal value of all characters within the quotes,
//with the exception of ‘$’, ‘‘’, ‘\’, and, when history expansion is enabled, ‘!’".
//
//tkn_nbr
//keeps monitoring whether str[i] is outside(x % 2 == 0) or inside(== 1)a quoting sequence.then
//	if (outside(or as soon as closed) && next char is either a space or EOL) then ===>>> tokenz++;
//basically it returns the number of words,flags and  quoted strings, aka the tokens.
//it doesn't count for an empty input(which should be handled by the prompt/readline loop)
int	tkn_nbr(char *str)
{
	int	i;
	int	n_tkn;
	int	quotes;
	int	w_quotes;


	i = -1;
	n_tkn = 0;
	quotes = 0;
	w_quotes = 0;
	while (str[++i])
	{
		if (str[i] == '"' && !quotes)
			w_quotes = (w_quotes + 1) % 2;
		else if (str[i] == '\'' && !w_quotes)
			quotes = (quotes + 1) % 2;
		if ((!quotes && !w_quotes) && !(str[i] == ' ')
			&& ((str[i + 1] == ' ') || !str[i + 1]))
			n_tkn++;
	}
	return (n_tkn);
}

	// count the lenght until the first occurence of char
	//(mainly to get the size necessary to malloc tokens
	// or to get the value of an index from an env var)
	int	ft_strchr_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (i >= (int) ft_strlen(str))
		return (-1);
	return (i);
}

//read the string and store the number of pipes, quotes and double quotes
//inside the shell's struct;at the moment is definetly incomplete, not considering quoted characters)
t_command	* count_pqwq(t_command *command, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			command->shell->mc_pipes++;
		if (str[i] == '\'')
			command->shell->mc_quotes++;
		if (str[i] == '\"')
			command->shell->mc_wquotes++;
	}
	printf("Pipes: %d\n",command->shell->mc_pipes);
	printf("Quotes: %d\n",command->shell->mc_quotes);
	printf("Double quotes: %d\n",command->shell->mc_wquotes);
	return (command);
}

char	**rip_and_tear(t_command *command, char *str)
{
//	int		i;
//	int		n_cmds;
	//char	**tkn_matrix;

//	i = 0;
//	n_cmds = 1;
	if ((count_pqwq(command, str))->shell->mc_quotes % 2
		|| (count_pqwq(command, str))->shell->mc_wquotes % 2)
		write(2, "syntax error, odd number of quotes or double quotes\n", 53);
	// while (str[i])
	// {
	// 	while (str[i] != )
	// }
	return (0);
}
