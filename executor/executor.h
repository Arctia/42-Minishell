#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../global.h"

/*
	***********************************************************
					executor.c
	***********************************************************
*/
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
					ft_execv.c
	***********************************************************
*/
char	*ft_append(char *path, t_command *cmd);
char	**ft_getpath(t_command *cmd);
void	ft_fixcommand(t_command *cmd);
char	*ft_findpath(t_command *cmd, int i);
// char	**ft_listtomatrix(t_command *cmd);
// char	**ft_addlinetomatrix(char **arr, char *line);
/*
	***********************************************************
					pipe.c
	***********************************************************
*/
void	ft_pipe(t_command *cmd, int std_cpy[2], pid_t pid);
void	ft_child(t_command *cmd, int **fd, int *i, int std_cpy[2]);
void	ft_wait(int i);
/*
	***********************************************************
					redir.c
	***********************************************************
*/
void	ft_redin(t_command *cmd, int *stdout_cpy);
void	ft_redout(t_command *cmd, int *stdout_cpy);
void	ft_redappend(t_command *cmd, int *stdout_cpy);
void	ft_heredoc(t_command *cmd, int *stdin_cpy);
/*
	***********************************************************
					redirpipe.c
	***********************************************************
*/
int		ft_redir(t_command *cmd, int *stdin_cpy, int *stdout_cpy);
void	ft_redirpipe(t_command *cmd, int *stdin_cpy, int *stdout_cpy);
void	ft_chooseredir(t_command *cmd, int *stdin_cpy, int *stdout_cpy);

#endif
