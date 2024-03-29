/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:15:03 by vgavioli          #+#    #+#             */
/*   Updated: 2023/04/01 12:16:51 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "../global.h"

# define HEREDOC_MSG	"\033[1;97m> \033[0m"

typedef struct s_redir
{
	int	n;
	int	lin;
	int	lout;
}	t_redir;

// redirection.c
void	exec_redir_pipe(t_command *cmd, int *stdin, int *stdout);
void	exec_redir(t_command *cmd, int *stdin, int *stdout);

// red_exec.c
void	red_append(t_command *cmd, t_redir red, int *stdin, int *stdout);
void	red_out(t_command *cmd, t_redir red, int *stdin, int *stdout);
void	red_here_doc(t_command *cmd, t_redir red, int *stdin);
void	red_in(t_command *cmd, t_redir red, int *stdin);

#endif