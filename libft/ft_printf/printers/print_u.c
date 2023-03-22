/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:28 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:24:30 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

void	calc_u_lengths(int len[4], long int val, t_pflags *tf)
{
	len[0] = number_digits(val);
	len[1] = tf->prec - len[0];
	if (len[1] > 0)
		len[2] = tf->length - (len[1] + len[0]);
	else
		len[2] = tf->length - len[0];
}

void	print_u(long int val, t_pflags *tf)
{
	int	len[4];

	calc_u_lengths(len, val, tf);
	print_spaces_before(len[2], tf);
	print_zeroes(len[2], tf);
	print_precision(len[1], tf);
	pf_putnbr_fd(val, 1, tf);
	print_spaces_after(len[2], tf);
}
