/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:00 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:25:01 by mbardett         ###   ########.fr       */
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
