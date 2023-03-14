#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../global.h"

typedef int	Pipe[2];
/*
	***********************************************************
					executor.c
	***********************************************************
*/
char	*ft_expander(char *str, char **env);
int		(*ft_builtin(char *str))(t_command *cmd);
void	ft_fixcommand(t_command *cmd);
void	ft_execv(t_command *cmd, pid_t pid);
void	ft_executor(t_command *parser);

/*
	***********************************************************
					execv.c
	***********************************************************
*/
char	*ft_append(char *path, t_command *cmd);
char	**ft_getpath(t_command *cmd, int i);
char	*ft_findpath(t_command *cmd, int i);
char	**ft_listtomatrix(t_command *cmd);
char    **ft_addlinetomatrix(char **arr, char *line);
/*
	***********************************************************
					pipe.c
	***********************************************************
*/
void	ft_pipe(t_command *cmd);
void	ft_pipeline(t_command *cmd, int std_cpy);
void	ft_pipejunior(t_command *cmd, int *fd, int n_pipe, int std_cpy);

// void	ft_pipejunior(t_command *cmd);
void	ft_fixstinpipe(t_command *cmd, Pipe output);
void	ft_execvepipe(t_command *cmd);
/*
	***********************************************************
					redir.c
	***********************************************************
*/
char	*ft_name(void);
void	ft_less(t_command *cmd);												//	<
void	ft_redir(t_command *cmd);										//	>
void	ft_moremore(t_command *cmd); // lo so è sbajato ma fa piu' ride		//	>>
void	ft_heredoc(t_command *cmd);											//	<<
/*
	***********************************************************
					utils
	***********************************************************
*/
void	ft_free_cmatrix(char **split_arr);
#endif
