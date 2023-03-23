/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:37 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:34 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (*exist == 1)
	{
		free(*str);
		(*str) = ft_strdup(arg);
	}
}
