#include "./../global.h"

/*##############################################################################
####	replace string: 
		 ° replace characters of a defined lenght string
##############################################################################*/
void	replace_string(char *s1, const char *s2)
{
	int	i;

	i = 0;
	s1[i] = s2[i];
	while (s2[i++])
		s1[i] = s2[i];
	//s1[i] = 0;
}

int	too_many_arguments(**char arg)
{
	if (arg[0] != 0)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	return (0);
}

/*##############################################################################
####	CD '-': 
		 ° if '-' is the argument try to go to previous folder if stored
		 	else write an error
		 ° store in *pfc the executed code status
##############################################################################*/
int	cmd_cd_previous_folder(char cmd[2048][2048], char pf[PATH_MAX], int *pfc)
{
	if (cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		if (pf[0] == 0)
		{
			pfn("cd: OLDPWD not set");
			*pfc = -1;
		}
		else
		{
			chdir(pf);
			printf("%s\n", pf);
			*pfc = 1;
		}
		return (1);
	}
	*pfc = 0;
	return (0);
}

/*##############################################################################
####	CD execution: 
		 ° if '-' is the argument go to previous fd stored in static pf
		 ° else try to move CWD into argument received
		 ° if error print no directory at path
									 - remove last printf after implementation
##############################################################################*/
int	execute_cd(t_command *cmd)
{
	char		actual_folder[PATH_MAX];
	static char	pf[PATH_MAX];
	int			error;
	int			pfc;

	error = -1;
	replace_string(actual_folder, getcwd(NULL, 0));
	if (cmd_cd_previous_folder(cmd->args, pf, &pfc) == 1)
	{
		if (pfc == -1)
			return (1);
		error = 0;
	}
	else
		error = chdir(cmd->args[1]);
	if (error)
	{
		printf("cd: no such file or directory: %s\n", cmd->args[1]);
		return (1);
	}
	replace_string(pf, actual_folder);
	printf("CWD: %s\n", getcwd(NULL, 0));
	return (0);
}

/*##############################################################################
####	Main CD function: 
		 ° return error if more than 1 argument
		 ° it also replace ~ with env HOME
##############################################################################*/
int	cd(t_command *cmd)
{
	char	argument[PATH_MAX];
	int		i;

	i = 0;
	if (too_many_arguments(cmd->args[2]) == 1)
		return (1);
	else if (cmd->args[1][0] == 0)
		replace_string(cmd->args[1], getenv("HOME"));
	else if (cmd->args[1][0] == '~')
	{	
		replace_string(argument, cmd->args[1]);
		replace_string(cmd->args[1], getenv("HOME"));
		while (argument[i])
		{
			if (argument[i] != '~')
				cmd->args[1][ft_strlen(cmd->args[1])] = argument[i];
			i++;
		}
	}
	return (execute_cd(cmd));
}

/* CD Testing Main */
/*int	main(int argc, char *argv[])
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	replace_string(cmd->args[0], "cd\0");
	if (argc >= 2)
		replace_string(cmd->args[1], argv[1]);
	//else if (argv[1] == NULL)
	//	replace_string(cmd->args[1], getenv("HOME"));
	if (argc >= 3)
		replace_string(cmd->args[2], argv[2]);
	cmd->args[1][0] = '~';
	cmd->args[1][1] = '/';
	cmd->args[1][2] = '.';
	cmd->args[1][3] = '.';
	cmd->args[1][4] = 0;
	cd(cmd);
	free(cmd);
	return (0);
}
*/
