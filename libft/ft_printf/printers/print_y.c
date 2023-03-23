/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:34 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:47:01 by vgavioli         ###   ########.fr       */
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
