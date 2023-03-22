#include "../global.h"
#include "../glob.h"
#include "../executor/executor.h"

#define YEL "\e[0;33m"
#define GRN "\e[0;32m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define WHITE "\e[0m"

//rip_and_tear is the name of a song from DOOM's O.S.T..
//I think it's quite an appropriate name for the process of splitting and
//tokenizing the input. And it's quite some badass music.
//If you don't agree, feel free to go and f##k off :)
static char *remove_home(char *str, char *home)
{
	char 	*new;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char), ft_strlen(str)  - ft_strlen(home) + 2);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == home[i])
			i++;
		else
			break ;
	}
	if (str[i])
		i++;
	while (str[i])
		new[j++] = str[i++];
	return (new);
}

static char	*our_prompt(t_hellmini *shell, char *str)
{
	char	*buff;
	char	*home_path;
	char	*new_path;

	home_path = exp_tkn("HOME", shell->env);
	buff = ft_calloc(sizeof(char), 2);
	buff[0] = '[';
	buff = ft_strjoin_free(buff, ft_itoa(get_ecode()), 1, 1);
	buff = ft_strjoin_free(buff, "] "BYEL, 1, 0);
	buff = ft_strjoin_free(buff, exp_tkn("USER", shell->env), 1, 1);
	buff = ft_strjoin_free(buff, PROMPT, 1, 0);
	if (!ft_strncmp(str, home_path, ft_strlen(home_path)))
	{
		buff = ft_strjoin_free(buff, "~/", 1, 0);
		new_path = remove_home(str, home_path);
		buff = ft_strjoin_free(buff, new_path, 1, 1);
		free(str);
	}
	else
		buff = ft_strjoin_free(buff, str, 1, 1);
	free(home_path);
	buff = ft_strjoin_free(buff, WHITE"$ ", 1, 0);
	return (buff);
}

static int	prompt_loop(t_hellmini *shell)
{
	while (TRUE)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_sigs_handler);
		shell->input = readline(our_prompt(shell, getcwd(NULL, 0)));
		if (!shell->input)
		{
			write(1, "\rexit\n", 7);
			break ;
		}
		if (ft_strncmp(shell->input, "", 1))
			add_history(shell->input);
		if (lexer_init(shell) == 0)
		{
			if (parser(shell) == SUCCESS)
				ft_executor(shell->current_cmd);
		}
		free_commands(shell);
	}
	clear_history();
	free_shell(shell);
	return (0);
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
