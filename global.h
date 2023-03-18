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
# include <errno.h>
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
# define TILDE 9
# define NOCMD 10
# define EMPTY -1

// Errors
# define ERR_DIR 126
# define ERR_UNK 127

# define PROMPT "\033[1;31mminisHELL\033[0m:"BGRN

//per far funzionare rl_replace_line
extern void	rl_replace_line(const char *text, int clear_undo);

//int *g_error_code;

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

}				t_hellmini;

typedef struct s_command
{
	char				*str;
	char				**tokens;
	int					spc[11];

	char				*command;
	char				**arguments;

	int					*red_type;
	char				**red;

	int		ret;

	struct s_command 	*next;
	struct s_command 	*prev;

	t_hellmini 			*shell;
}	t_command;

// builtins
int		redirector(t_command *cmd);
int		unset(t_command *cmd);
int		cd(t_command *cmd);
int 	pwd(t_command *cmd);
int		echo(t_command *cmd);
int		env(t_command *cmd);
int		ms_exit(t_command *cmd);

// expander/expander.c
void	expander(t_command *cmd);

// expander/expander_utils.c
char	*exp_tkn(char *str, char **env);

// expander/expander_utils.c
char	**ft_arrdup(char **arr);

// main/init.c
void					init_shell(t_hellmini *shell, char **env);
t_command				*init_command(t_hellmini *shell);
void					set_ecode(int code);
void					control_c_signal(int sig);

// main/free_structs.c
void	free_commands(t_hellmini *shell);
void	free_shell(t_hellmini *shell);

// parser.c
int		parser(t_hellmini *sh);

// lexer/lexer.c
int		lexer_init(t_hellmini *shell);
// lexer/lexer_splitter.c
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

//signals.c
//void	ft_suppress_output(void);
void	ft_sigs_handler(int sig);

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

#endif
