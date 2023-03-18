#include "../global.h"
#include "../executor/executor.h"
#include "prompt_and_signals.h"
#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
//# define PROMPT "\033[1;31mminisHELL$:\033[0m "

//rip_and_tear is the name of a song from DOOM's O.S.T..
//I think it's quite an appropriate name for the process of splitting and
//tokenizing the input. And it's quite some badass music.
//If you don't agree, feel free to go and f##k off :)

static int	prompt_loop(t_hellmini *shell)
{
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		signal(SIGINT, ft_sigs_handler);
		shell->input = readline(PROMPT);
		if (!shell->input)
		{
			write(1, "\rexit\n", 7);
			rl_redisplay();
			exit(0);
		}
		if (ft_strncmp(shell->input, "", 1))
			add_history(shell->input);
		if (shell->input[0] != '\0')
		{
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
		}
		//pfn("\n%3t enter free");
		free_commands(shell);
	}
	clear_history();
	free_shell(shell);
	//rip_and_tear(shell->current_cmd, shell->current_cmd->command);
	return (0);
}
// int	prompt_loop(t_hellmini *shell)
// {
// //signal
// 	while(1)
// 	{
// 		// signal(SIGINT, sigint_handler);
// 		// signal(SIGQUIT, sigquit_handler);
// 		signal(SIGINT, ft_sigs_handler);
// 		signal(SIGQUIT, ft_sigs_handler);
// 		//sigquit_macro(SIGQUIT, shell);
// 		shell->input = readline(PROMPT);
// 		if (!shell->input)
// 		{
// 			// rl_replace_line("\033[1;31mminisHELL$:\033[0m exit\n", 0);
// 			// shell->input = ft_strdup("exit");

// 			// rl_redisplay();
// 			// printf("\033[1;31mminisHELL$:\033[0m exit\n");
// 			rl_replace_line("exit", 0);
// 			//rl_redisplay();
// 			//write(1, "exit", 4);
// 			exit(0);
// 		}
// //			return (0 * write(1, "exit\n", 5));
// 		if (ft_strncmp(shell->input, "", 1))
// 			add_history(shell->input);

// 		//command_init(&shell);
// 		// if (!ft_strncmp(shell->input, "exit\n", 5))
// 		// {
// 		// 	//ft_free_structs();
// 		// 	exit(0);
// 		// }
// 	//	exp_tkn("$user", shell->env);
// 	}

// 	//rip_and_tear(shell->current_cmd, shell->current_cmd->command);
// 	return (0);
// }

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
