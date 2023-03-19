#include "../global.h"
#include "../glob.h"
#include "../executor/executor.h"
//#include "prompt_and_signals.h"

#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define WHITE "\e[0m"
//# define PROMPT "\033[1;31mminisHELL$:\033[0m "

//rip_and_tear is the name of a song from DOOM's O.S.T..
//I think it's quite an appropriate name for the process of splitting and
//tokenizing the input. And it's quite some badass music.
//If you don't agree, feel free to go and f##k off :)



static char	*our_prompt(t_hellmini *shell, char *str)
{
	char	*buff;
	char	*path;
	char	*new_path;

	path = exp_tkn("HOME", shell->env);
	buff = ft_calloc(sizeof(char), 2);
	buff[0] = '[';
	buff = ft_strjoin_free(buff, ft_itoa(get_ecode()), 1, 1);
	buff = ft_strjoin_free(buff, "] "BYEL, 1, 0);
	buff = ft_strjoin_free(buff, exp_tkn("USER", shell->env), 1, 1);
	buff = ft_strjoin_free(buff, PROMPT, 1, 0);
	
	if (!ft_strncmp(str, path, ft_strlen(path)))
	{
		new_path = ft_strtrim(str, path);
		buff = ft_strjoin_free(buff, "~/", 1, 0);
		buff = ft_strjoin_free(buff, new_path, 1, 1);
		free(str);
	}
	else
		buff = ft_strjoin_free(buff, str, 1, 1);
	free(path);
	buff = ft_strjoin_free(buff, WHITE"$ ", 1, 0);
	return (buff);
}

static int	prompt_loop(t_hellmini *shell)
{
	signal(SIGQUIT, SIG_IGN);
	while(TRUE)
	{
		signal(SIGINT, ft_sigs_handler);
		shell->input = readline(our_prompt(shell, getcwd(NULL, 0)));
		if (!shell->input)
		{
			write(1, "\rexit\n", 7);
			break ;
		}
		if (ft_strncmp(shell->input, "", 1))
			add_history(shell->input);
		pfn("%3t enter lexer");
		if (lexer_init(shell) == 0)
		{
			pfn("\n%3t enter parser");
			if (parser(shell) == SUCCESS)
			{
				pfn("\n%3t enter executor");
				ft_executor(shell->current_cmd);
			}
		}
		//pfn("\n%3t enter free");
		free_commands(shell);
	}
	clear_history();
	free_shell(shell);
	return (0);
}

void	control_c_signal(int sig)
{
	if (sig == SIGINT)
		pfn("^C\n");
	set_ecode(130);
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_hellmini	*shell;

	(void)argc;
	(void)argv;

	shell = (t_hellmini *) malloc(sizeof(t_hellmini));
	if (!shell)
		return (EXIT_FAILURE);
	init_shell(shell, env);
	prompt_loop(shell);
	return (0);
}
