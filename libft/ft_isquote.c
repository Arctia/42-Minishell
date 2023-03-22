/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:09:41 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:09:43 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* if char is a quote return it's value, else return null character */
char	ft_isquote(char ch)
{
	if (ch == '\'' || ch == '"')
		return (ch);
	return ('\0');
}
