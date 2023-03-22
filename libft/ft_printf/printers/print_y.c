/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:34 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:25:36 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../libft.h"
#include "./../ft_printf.h"
#include <stdio.h>

void	print_y(t_pflags *tf)
{	
	static int	counter;
	char		*str;

	if (!counter)
		counter = 0;
	str = ft_itoa(counter);
	write(1, str, pf_strlen(str));
	write(1, ".", 1);
	tf->dimension += pf_strlen(str) + 1;
	counter++;
	free(str);
}
