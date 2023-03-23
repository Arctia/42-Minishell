/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:00 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:46:58 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

void	print_spaces_before(int n, t_pflags *tf)
{
	if (tf->length && !tf->minus && !tf->zero)
		print_n0s(n, ' ', tf);
}

void	print_zeroes(int n, t_pflags *tf)
{
	if (tf->length && tf->zero)
		print_n0s(n, '0', tf);
}

void	print_precision(int n, t_pflags *tf)
{
	if (tf->point && tf->prec)
		print_n0s(n, '0', tf);
}

void	print_spaces_after(int n, t_pflags *tf)
{
	if (tf->length && tf->minus)
		print_n0s(n, ' ', tf);
}
