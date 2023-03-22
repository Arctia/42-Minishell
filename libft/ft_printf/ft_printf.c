/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:39:48 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 22:39:49 by mbardett         ###   ########.fr       */
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
