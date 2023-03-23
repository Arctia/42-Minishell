/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:54 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:46:59 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

void	print_c(char ch, t_pflags *tf)
{
	int	len;

	len = (tf->length - 1);
	print_spaces_before(len, tf);
	write(1, &ch, 1);
	tf->dimension++;
	print_spaces_after(len, tf);
}
