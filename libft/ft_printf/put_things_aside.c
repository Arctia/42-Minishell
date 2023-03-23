/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_things_aside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:06:06 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 10:47:07 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	isdigitaft(int ch, char start)
{
	if (ch <= '9' && ch >= start)
		return (1);
	return (0);
}

void	pf_putchar_fd(char c, int fd, t_pflags *tf)
{
	write(fd, &c, 1);
	tf->dimension += 1;
}

void	pf_putnbr_fd(long int n, int fd, t_pflags *tf)
{
	if (n == -2147483648)
	{
		write(fd, "2147483648", 10);
		tf->dimension += 10;
	}
	else
	{
		if (n < 0)
			n *= -1;
		if (n > 9)
		{
			pf_putnbr_fd(n / 10, fd, tf);
			pf_putnbr_fd(n % 10, fd, tf);
		}
		else
		{
			pf_putchar_fd(n + '0', fd, tf);
		}
	}
}

size_t	pf_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (6);
	while (str[i])
		i++;
	return (i);
}
