#ifndef GLOBAL_H
# define GLOBAL_H

# include "./libft/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

//per far girare sigaction
//#define _POSIX_C_SOURCE 199309L
# define _POSIX_C_SOURCE 200809L

// Constant declarations
//# define NAME_MAX 255
//# define PATH_MAX 1024
# define SUCCESS 0
# define FAIL 1


// Operator presence
# define PIPE 0
# define SQUOTE 1
# define DQUOTE 2
# define MQUOTE 3
# define REDIN 4
# define REDOUT 5
# define REDAPP 6
# define HERDOC 7
# define CASH 8
# define EMPTY -1

# define PROMPT "\033[1;31mminisHELL$:\033[0m "

//per far funzionare rl_replace_line
extern void	rl_replace_line(const char *text, int clear_undo);

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 				**env;

	char				*input;
	struct s_command 	*current_cmd;

	int					exit_status;
	int					mc_pipes;
	int					mc_quotes;
	int					mc_wquotes;

}           t_hellmini;

typedef struct s_command
{
	char				*str;
	char				**tokens;
	int					spc[9];

	char				*command;
	char				**arguments;

	int					*red_type;
	char				**red;

	int		ret;

	struct s_command 	*next;
	struct s_command 	*prev;

	t_hellmini 			*shell;
}	t_command;

// expander/expander.c
void					expander(t_command *cmd);

// expander/expander_utils.c
char    				**ft_arrdup(char **arr);

// main/free_structs.c
void					free_commands(t_hellmini *shell);
void					free_shell(t_hellmini *shell);

// parser.c
int						parser(t_hellmini *sh);

// lexer/lexer.c
int     				lexer_init(t_hellmini *shell);
// lexer/lexer_splitter.c
void					lexer_error(char *message);
char					*split_operator(char *line, int *ff, int not_new);
char					*split_line(char *line);

// expander/expander_utils.c
char					*exp_tkn(char *str, char **env);


//signals.c
void					ft_suppress_output(void);
void					sigint_handler(int sig);
void					sigquit_handler(int sig);
void					sigquit_macro(int sig, t_hellmini *shell);
void					*ft_handler(int sig);
void					ft_sigs_handler(int sig);

#endif
