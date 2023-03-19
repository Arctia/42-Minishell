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
void	ft_execv(t_command *cmd, pid_t pid, int *status);
void	ft_executor(t_command *parser);

/*
	***********************************************************
					execute_process.c
	***********************************************************
*/
void	execute_process(t_hellmini *shell, char *path, char **args);

/*
	***********************************************************
					execv.c
	***********************************************************
*/
char	*ft_append(char *path, t_command *cmd);
//char	**ft_getpath(t_command *cmd, int i);
char	*ft_findpath(t_command *cmd, int i);
char	**ft_listtomatrix(t_command *cmd);
char    **ft_addlinetomatrix(char **arr, char *line);
/*
	***********************************************************
					pipe.c
	***********************************************************
*/
void	ft_pipe(t_command *cmd);
void	ft_dupandclose(int std_cpy[2], int **fd, int i, pid_t pid);
void	ft_pipeline(t_command *cmd);
void	ft_pipejunior(t_command *cmd, int *fd, int n_pipe, int std_cpy);

// void	ft_pipejunior(t_command *cmd);
void	ft_fixstinpipe(t_command *cmd, Pipe output);
/*
	***********************************************************
					redir.c
	***********************************************************
*/
char	*ft_name(void);
int		ft_redir(t_command * cmd);
int		ft_redir_pipe(t_command * cmd);
void	ft_chooseredir(t_command *cmd);


void	ft_redin(t_command *cmd);												//	<
void	ft_redout(t_command *cmd);										//	>
void	ft_redappend(t_command *cmd); // lo so è sbajato ma fa piu' ride		//	>>
void	ft_heredoc(t_command *cmd);											//	<<
/*
	***********************************************************
					utils
	***********************************************************
*/
void	ft_free_cmatrix(char **split_arr);
#endif
