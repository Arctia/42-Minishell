/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_prints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:05 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:25:09 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	number_digits(long int n)
{
	int	digits;

	digits = 1;
	if (n == -2147483648)
		digits = 11;
	else
	{
		if (n < 0)
			n = n * (-1);
		while (n >= 10)
		{
			digits += 1;
			n = n / 10;
		}
	}
	return (digits);
}

void	print_0s(int num, t_pflags *tf, char ch)
{
	int	t_digits;

	t_digits = tf->space + number_digits(num);
	if (!tf->prec)
		t_digits += tf->plus;
	if (!tf->plus && num < 0 && !tf->prec)
		t_digits++;
	while (tf->length > t_digits || tf->prec > t_digits)
	{
		pf_putchar_fd(ch, 1, tf);
		t_digits++;
	}
}

void	print_n0s(int n, char ch, t_pflags *tf)
{
	while (n-- > 0)
		pf_putchar_fd(ch, 1, tf);
}
