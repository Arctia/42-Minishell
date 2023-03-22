/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:54 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:24:56 by mbardett         ###   ########.fr       */
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
