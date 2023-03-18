
#include "../global.h"

/*##############################################################################
####	CD '-': 
		 ° if '-' is the argument try to go to previous folder if stored
		 	else write an error
		 ° store in *pfc the executed code status
############################################################################*/
static int	cd_prev_folder(t_hellmini *shell, char *arg, int *pfc)
{
	char	*old_path;

	old_path = exp_tkn("OLDPWD", shell->env);
	if (arg[0] == '-' && arg[1] == '\0')
	{
		if (old_path == NULL)
		{
			pfn("bash: cd: OLDPWD not set");
			*pfc = -1;
		}
		else
		{
			chdir(old_path);
			pfn("%s", old_path);
			ft_free_ptr(old_path);
			*pfc = 1;
		}
		return (1);
	}
	*pfc = 0;
	ft_free_ptr(old_path);
	return (0);
}

/*##############################################################################
####	CD execution: 
		 ° if '-' is the argument go to previous fd stored in static pf
		 ° if error print no directory at path
									 - remove last printf after implementation
############################################################################*/
static int	cd_execute(t_command *cmd)
{
	int	error;
	int	pfc;

	pfc = 0;
	error = -1;
	if (cd_prev_folder(cmd->shell, cmd->arguments[1], &pfc) == 1)
	{
		if (pfc == -1)
			return (1);
		error = 0;
	}
	else
		error = chdir(cmd->arguments[1]);
	if (error)
	{
		change_code(1);
		pfn("bash: cd: %s: Not a directory");
		return (1);
	}
	pfn("CWD: %s", getcwd(NULL, 0));
	return (0);
}

/*##############################################################################
####	Replace empty arguments: 
		 ° allocate arguments
		 ° store home path in first argument
############################################################################*/
static void	cd_replace_null(t_command *cmd, char *str)
{
	int		i;

	ft_free_cmatrix(cmd->arguments);
	cmd->arguments = ft_calloc(sizeof(char *), 3);
	cmd->arguments[0] = ft_strdup(cmd->command);
	cmd->arguments[1] = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		cmd->arguments[1][i] = str[i];
		i++;
	}
	cmd->arguments[2] = NULL;
}

/*##############################################################################
####	Main CD function: 
		 ° return error if more than 1 argument
		 ° replace no argument with HOME path
############################################################################*/
int	cd(t_command *cmd)
{
	char	*home;

	home = exp_tkn("HOME", cmd->shell->env);
	if (cmd->arguments[1] && cmd->arguments[2])
	{
		pfn("bash: cd: too many arguments");
		return (1);
	}
	else if (!(cmd->arguments[1]))
		cd_replace_null(cmd, home);
	ft_free_ptr(home);
	return (cd_execute(cmd));
}
