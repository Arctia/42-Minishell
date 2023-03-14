/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariani <mmariani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:09:10 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/14 20:50:10 by mmariani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

int	ft_printf(const char *str, ...)
{
	char		*start;
	char		*seg;
	va_list		valist;
	t_pflags	tf;

	tf.dimension = 0;
	seg = (char *) str;
	va_start(valist, str);
	while (*seg)
	{
		reset_struct(&tf);
		start = seg;
		seg = find_percent(seg);
		print_previous_part(start, seg - start, &tf);
		seg = set_flags(seg, &tf);
		check_flags(&tf);
		print_element(&tf, valist);
	}
	va_end(valist);
	return (tf.dimension);
}

int	pfn(const char *str, ...)
{
	// return 0;
	char		*start;
	char		*seg;
	va_list		valist;
	t_pflags	tf;

	tf.dimension = 0;
	seg = (char *) str;
	va_start(valist, str);
	while (*seg)
	{
		reset_struct(&tf);
		start = seg;
		seg = find_percent(seg);
		print_previous_part(start, seg - start, &tf);
		seg = set_flags(seg, &tf);
		check_flags(&tf);
		print_element(&tf, valist);
	}
	write(1, "\n", 1);
	va_end(valist);
	return (tf.dimension + 1);
}

int	ft_printfd(const char *str, ...)
{
	char		*start;
	char		*seg;
	va_list		valist;
	t_pflags	tf;

	if (!DEBUGGING)
		return (0);
	tf.dimension = 0;
	seg = (char *) str;
	va_start(valist, str);
	while (*seg)
	{
		reset_struct(&tf);
		start = seg;
		seg = find_percent(seg);
		print_previous_part(start, seg - start, &tf);
		seg = set_flags(seg, &tf);
		check_flags(&tf);
		print_element(&tf, valist);
	}
	va_end(valist);
	return (tf.dimension);
}

int	pfnd(const char *str, ...)
{
	char		*start;
	char		*seg;
	va_list		valist;
	t_pflags	tf;

	if (!DEBUGGING)
		return (0);
	tf.dimension = 0;
	seg = (char *) str;
	va_start(valist, str);
	while (*seg)
	{
		reset_struct(&tf);
		start = seg;
		seg = find_percent(seg);
		print_previous_part(start, seg - start, &tf);
		seg = set_flags(seg, &tf);
		check_flags(&tf);
		print_element(&tf, valist);
	}
	write(1, "\n", 1);
	va_end(valist);
	return (tf.dimension + 1);
}
