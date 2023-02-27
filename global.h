#ifndef GLOBAL_H
# define GLOBAL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>

// Constant declarations
# define NAME_MAX 255
# define PATH_MAX 1024

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 		**env;

	int			*exit_status;
	struct s_command 	*cmd;


    pid_t 		pid; // maybe
}           t_hellmini;

typedef struct s_command
{
	char	*command;
	char	**flags;
	char	**arguments;

	int		ret;

	struct s_command *next;
	struct s_command *prev;

	t_hellmini *shell;
}	t_command;

#endif
