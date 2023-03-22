/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:24 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:21:25 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "./../global.h"

// expander.c
void	expander(t_command *cmd);

// expander_utils.c
int		expand_question(char buff[4095], char *(*str), int *i);
void	expand_tilde(t_hellmini *sh, char buff[4095], char *(*str), int *i);
void	to_next_single_quote(char *(*str), char buff[4095], int *i);
char	*get_string_to_expand(char *(*str));
char	*exp_tkn(char *str, char **env);

#endif