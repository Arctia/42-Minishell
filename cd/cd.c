
#include "../global.h"

/*##############################################################################
####	CD '-': 
		 ° if '-' is the argument try to go to previous folder if stored
		 	else write an error
		 ° store in *pfc the executed code status
############################################################################*/
static int	cd_prev_folder(char *arg, int *pfc)
{
	char	*old_path;

	old_path = exp_tkn("", shell->env);
	if (arg[0] == '-' && arg[1] == '\0')
	{
		if (old_path == NULL)
		{
			pfn("cd: OLDPWD not set");
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
static int	cd_execute(t_command *cmd, t_hellmini *shell)
{
	int	pfc;

	pfc = 0;
	if (cd_prev_folder(cmd->arguments[0], &pfc) == 1)
	{
		if (pfc == -1)
			return (1);
		error = 0;
	}
	else
		error = chdir(cmd->arguments[0]);
	if (error)
	{
		//pfn("cd: no such file or directory: %s\n", cmd->args[1]);
		perror("cd: ");
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
	int	i;

	ft_free_cmatrix(cmd->arguments);
	cmd->arguments = malloc(sizeof(char *) * 2);
	cmd->arguments[0] = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		cmd->arguments[0][i] = str[i];
		i++;
	}
	cmd->arguments[1] = NULL;
}

/*##############################################################################
####	Main CD function: 
		 ° return error if more than 1 argument
		 ° replace no argument with HOME path
############################################################################*/
int	cd(t_command *cmd)
{
	char	argument[PATH_MAX];
	char	*home;
	int		i;

	i = 0;
	home = get_env_var("HOME");
	if (cmd->arguments[0] && cmd->arguments[1])
	{
		pfn("cd: too many arguments");
		return (1);
	}
	else if (!(cmd->arguments[0]))
		cd_replace_null(cmd, home);
	ft_free_ptr(home);
	return (execute_cd(cmd));
}
