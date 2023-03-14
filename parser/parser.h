#ifndef PARSER_H
# define PARSER_H

# include "./../global.h"

// ps_utils.c
int		to_next_quote(char *str, int i, char quote);
void	move_to_next_char(t_command *cmd);
int		until_space(const char *str);

#endif