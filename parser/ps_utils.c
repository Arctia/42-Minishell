
#include "./parser.h"

/*##############################################################################
#	Help Functions
############################################################################*/
int	until_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isnotspace(str[i]))
		i++;
	return (i);
}

void	move_to_next_char(t_command *cmd)
{
	while (cmd->str[0] && ft_isspace(cmd->str[0]))
		cmd->str++;
}

int	to_next_quote(char *str, int i, char quote)
{
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}
