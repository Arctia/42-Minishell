#include "parser.h"

void	ps_move_to_next_char(t_command *cmd)
{
	while (cmd->str[0] && ft_isspace(cmd->str[0]))
		cmd->str++;
}
