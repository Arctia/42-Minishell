

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
		replace_null(cmd, home);
	return (execute_cd(cmd));
}