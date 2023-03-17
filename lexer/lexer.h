
#ifndef LEXER_H
# define LEXER_H

# include "./../global.h"

# define UNEXPECTED "()\\*;"

// lexer_splitter.c
char	*split_operator(char *line, int *ff, int not_new);
int		split_operator_line(char *line, int i);
void	lexer_error(char *message); 

// lexer_syntax.c
int		lx_error(unsigned char chr);
int		syntax_check_2(char *line);

#endif
