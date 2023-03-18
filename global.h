#ifndef GLOBAL_H
# define GLOBAL_H

// e libft?
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
// # define PATH_MAX 1024
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

//per far funzionare rl_replace_lline
extern void	rl_replace_line(const char *text, int clear_undo);

// Struct declarations --> Every array/matrix should be null terminated
typedef struct s_hellmini
{
	char 				**env;

	int					exit_status;
	char				*input;
	struct s_command 	*current_cmd;
	int					mc_pipes;
	int					mc_quotes;
	int					mc_wquotes;

//	pid_t				pid; // maybe
}           t_hellmini;

//words_operators e'la prima splittata(" ")dell'input, ergo la prima tokenizzazione;
//potrebbe servirne una ulteriore per semplificare la lettura del codice(in generale ma
//soprattutto in presenza di < > << >>)
typedef struct s_command
{
	char				*str;
	char				**tokens;
	int					spc[9];

	char				*command;
	char				**flags; // useless (?)
	char				**arguments;

	int					*red_type;
	char				**red;

	int		ret;

	struct s_command 	*next;
	struct s_command 	*prev;

	t_hellmini 			*shell;
}	t_command;

// main/free_structs.c
void					free_commands(t_hellmini *shell);
void					free_shell(t_hellmini *shell);

// parser.c
int						parser(t_hellmini *sh);

/*lexer.c
			lexer.c			*/
int     				lexer_init(t_hellmini *shell);
/*			lexer_splitter.c  */
void					lexer_error(char *message);
char					*split_operator(char *line, int *ff, int not_new);
char					*split_line(char *line);

//tokenizer.c
int						tkn_nbr(char *str);
int 					ft_strchr_len(char *str, char c);
t_command				* count_pqwq(t_command *command, char *str);
void					the_expanse(t_command *cmd);
char					**rip_and_tear(t_command *command, char *str);

//expander_utils.c
int						mini_sort(char *str);
int						expansion_explosion(char *str, char tmp[4095], int *index, char **env);
char					*new_tkn_aux(char *str, t_command cmd, int i, int k);
char					*new_tkn(char *ol_tkn, t_command *cmd);

//expander.c
void					free_arr(char **split_arr);
char					**ft_arrdup(char **arr);
char					*exp_tkn(char *str, char **env);

//expander_utils.c
char					*check_key_value(char *key_value);

//env_handlers.c
void					init_shell_env(char **pr_env, t_hellmini shell);

//signals.c
void					ft_suppress_output(void);
void					sigint_handler(int sig);
void					sigquit_handler(int sig);
void					sigquit_macro(int sig, t_hellmini *shell);
void					*ft_handler(int sig);
void					ft_sigs_handler(int sig);

//export.c
char 					**exp_(t_hellmini shell);

//export_utils.c
char					*full_key_value(char *key_value);
char					*check_key_value(char *key_value);
void					sort_export(char **key_value, char ** env_cpy, char **big_buff);

// int						alpha_cmp(char *str1, char *str2);
void					alpha_sort(char **mtrx);
void					export_aux(char **key_value, char **env_cpy);
int						ft_export(char **key_value, t_hellmini *shell);

//main.c
int						prompt_loop(t_hellmini *shell);
void					init_shell(t_hellmini *shell);
#endif
