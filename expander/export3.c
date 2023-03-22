#include "../global.h"

int	export_check_argument(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (ft_printf("bash: export: `=': not a valid identifier\n"));
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
		{
			return (
				ft_printf("bash: export: `%s': not a valild identifier\n",
					str));
		}
	}
	return (0);
}

void	val_env_part_2(int *exist, char **str, char *arg)
{
	*exist = export_compare_values(*str, arg);
	if (*exist)
	{
		free(str);
		(*str) = ft_strdup(arg);
	}
}
