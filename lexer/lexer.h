/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:00 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:41 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./../global.h"

# define UNEXPECTED "()\\*;"

int		check_closures(char *line, int i);
int		ms_isoperator(char c);

// lexer_splitter.c
char	*split_operator(char *line, int *ff, int not_new);
int		split_operator_line(char *line, int i);
int		check_operator(char *line, int i);
void	lexer_error(char *message);

// lexer_syntax.c
int		check_syntax(char *line, int i);
void	move_to_next_char(char **line);
int		lx_error(unsigned char chr);
int		syntax_check_2(char *line);

#endif
