/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:07:00 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:46:57 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		line_len_n(char *str);
size_t	gnl_strlen(char *str);
char	*free_buffer(char *buffer);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strchr(char *s, int c);

#endif