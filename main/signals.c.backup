#include "../global.h"

//#define _POSIX_C_SOURCE 199309L#define _POSIX_C_SOURCE 199309L

// Ctrl-C(SIGINT)
void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

//Ctrl-C 2.0(SIGINT)
void	sigint_help(char **envp)
{
	int		child;
	char	*cmd[3];

	cmd[0] =ft_strdup("stty");
	cmd[1] = ft_strdup("-echotcl");
	cmd[2] = "\0";
	child = fork();
	if (!child)
	{
		execve("/bin/stty", cmd, envp);
	}
	waitpid(child, NULL, 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// void	ft_re_canon()
// {
// 	struct termios	raw_settings;

// 	raw_settings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
// 						| INLCR | IGNCR | ICRNL | IXON);
// 	raw_settings.c_oflag &= ~OPOST;
// 	raw_settings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
// 	raw_settings.c_cflag &= ~(CSIZE | PARENB);
// 	raw_settings.c_cflag |= CS8;
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_settings);
// 	write(1, "gesuappeso\n", 12);
// }



//Ctrl-D
void	sigquit_handler(int sig)
{
	int	ch_pid;

	ch_pid = fork();
	(void)sig;
	waitpid(ch_pid, NULL, 0);
	exit(0);
}

//Ctrl-D migliorato?
// void	sigquit_macro(int sig, t_hellmini *shell)
// {
// 	struct sigaction sa;
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.__sigaction_u.__sa_sigaction = ft_handler;

// 	// if (!sigaction(SIGQUIT, NULL, NULL))
// 	// {
// 	// 	exit_msg = ft_strjoin(PROMPT, "exit\n");
// 	// 	shell->input = readline(exit_msg);
// 	// }
// 	// free(exit_msg);
// 	sigquit_handler(sig);
// }
//CTRL-/ (SIG_QUIT)
//per i children?serve?

void	*ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		write(1, "\n", 1);
		ft_suppress_output();

		rl_on_new_line();
		rl_redisplay();;
	}
	if (sig == SIGQUIT)
		(void)sig;
	return (NULL);
}
//QUALCUNO PENSI AI BAMBINI!!!!(cit.)
