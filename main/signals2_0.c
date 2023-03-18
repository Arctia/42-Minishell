#include "../global.h"

static void	ft_suppress_output(void)
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &new_settings);
	//if (!tcgetattr(STDIN_FILENO, &new_settings))
	//old_settings = new_settings;
	//	write(1, "dioladrobastardo\n", 18);
	//ft_re_canon();
	new_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &new_settings);
	// write(1, "exit\n", 5);
	// if(!tcsetattr(STDOUT_FILENO, 0, &new_settings))
	// 	write(1,"bioparco\n", 10);
		//exit(0);
}

void	ft_sigs_handler(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		write(1, "\n", 1);
		ft_suppress_output();
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
