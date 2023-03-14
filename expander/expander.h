
#ifndef EXPANDER_H
# define EXPANDER_H

# include "./../global.h"

// expander.c
void	expander(t_command *cmd);

// expander_utils.c
void	expand_tilde(t_hellmini *sh, char buff[4095], char *(*str), int *i);
void	to_next_single_quote(char *(*str), char buff[4095], int *i);
char	*get_string_to_expand(char *(*str));
char	*exp_tkn(char *str, char **env);
char	**ft_arrdup(char **arr);

#endif