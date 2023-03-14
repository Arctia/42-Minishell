#include "executor.h"

// typedef int	Pipe[2];

/*
	***********************************************************
					ft_execvepipe
	***********************************************************
	different ft_execv without fork i don't know if needed
*/

void	ft_execvepipe(t_command *cmd)
{
	char	*path;
	char	**arg;

	arg = ft_listtomatrix(cmd);
	path = ft_findpath(cmd, 0);
	if (execve(path, arg, cmd->shell->env) == -1)
		perror("execution failed");
	ft_free_cmatrix(arg);
	free(path);
	// exit(EXIT_FAILURE);
}

/*
	***********************************************************
					ft_fixstinpipe
	***********************************************************
	dealt with the in and out of command and recall ft pipejunior 
	for eventually other pipe 
*/

void	ft_fixstinpipe(t_command *cmd, Pipe output)
{
	dup2(output[1], 1);
	close(output[0]);
	close(output[1]);
	if (cmd->next->spc[PIPE] == 0)
		return ;
	ft_pipejunior(cmd);
}

/*
	***********************************************************
					ft_pipejunior
	***********************************************************
	pipe fork chek
	maybe ft_execpipe must be bring here
*/

void	ft_pipejunior(t_command *cmd)
{
	pid_t	pid;
	Pipe	input;

	if (cmd->spc[PIPE])
	{
		if (pipe(input) != 0)
			perror("failed to create pipe");
		pid = fork();
		if ((pid < 0))
			perror("failed to fork");
		if (!pid)
			ft_fixstinpipe(cmd, input);
		dup2(input[0], 0);
		close(input[0]);
		close(input[1]);
	}
	// waitpid(0, &status ,0);	//? not sure if here or in ft_executor with a while loop or in ft pipe
	ft_execvepipe(cmd);
}

/*
	***********************************************************
					ft_pipe
	***********************************************************
	making start the magic trick 
	maybe ft_execpipe must be bring in an other function
	i've to study the  if else state to break the while 
*/

void	ft_pipe(t_command *cmd)
{
	pid_t	pid;
	int		status;

	while (cmd->spc[PIPE] 
		&& cmd->next->spc[PIPE])	// check it
	{
		pid = fork();
		if (pid < 0)
			perror("failed to fork");
		if (pid != 0)
			return ;	//  wait??
		ft_pipejunior(cmd);
		if (cmd->spc[PIPE])
			cmd = cmd->next;
		waitpid(0, &status, 0);		//? not sure if here or in ft_executor with a while loop
	}
}
