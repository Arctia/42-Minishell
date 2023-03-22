/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:34 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:24:36 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../ft_printf.h"

int	print_s_true(int *mov, int tot, int sl, t_pflags *tf)
{
	if (*mov < 0)
		*mov = 0;
	if (*mov > 0 && *mov < tot && (tf->length > 0 && !tf->minus))
	{
		*mov += 1;
		return (1);
	}
	else if (*mov >= 0 && *mov < sl && (tf->length == 0 || tf->minus))
	{
		*mov += 1;
		return (1);
	}
	return (0);
}

void	calc_string_length(int *len, char *str, t_pflags *tf)
{
	len[0] = pf_strlen(str);
	len[1] = len[0];
	if (tf->length > 0)
		len[1] = tf->length;
	if (tf->point && len[0] > tf->prec)
		len[0] = tf->prec;
}

void	print_null(t_pflags *tf)
{
	pf_putchar_fd('(', 1, tf);
	pf_putchar_fd('n', 1, tf);
	pf_putchar_fd('u', 1, tf);
	pf_putchar_fd('l', 1, tf);
	pf_putchar_fd('l', 1, tf);
	pf_putchar_fd(')', 1, tf);
}

void	print_s(char *str, t_pflags *tf)
{
	int	len[2];
	int	mov;

	mov = 0;
	calc_string_length(len, str, tf);
	while (tf->minus == 0 && tf->length > 0 && mov++ < (len[1] - len[0]))
		pf_putchar_fd(' ', 1, tf);
	mov--;
	while (print_s_true(&mov, len[1], len[0], tf))
	{
		if (str == NULL)
		{
			print_null(tf);
			break ;
		}
		else if (str[0])
			pf_putchar_fd(str++[0], 1, tf);
		else
			break ;
	}
	while (tf->minus && tf->length > 0 && mov++ < len[1])
		pf_putchar_fd(' ', 1, tf);
}
