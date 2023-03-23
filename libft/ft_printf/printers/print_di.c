/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:47 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:47:01 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

void	print_i(int i, t_pflags *tf)
{	
	if (tf->plus == 1 && i > -1)
		pf_putchar_fd('+', 1, tf);
	else if (i < 0)
		pf_putchar_fd('-', 1, tf);
	if (tf->space == 1 && i > -1)
	{
		pf_putchar_fd(' ', 1, tf);
		print_0s(i, tf, ' ');
	}
	if (tf->zero || tf->point)
		print_0s(i, tf, '0');
	pf_putnbr_fd(i, 1, tf);
	if (tf->minus == 1)
		print_0s(i, tf, ' ');
}
