/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgavioli <vgavioli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:50 by vgavioli          #+#    #+#             */
/*   Updated: 2023/03/23 11:10:33 by vgavioli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global.h"

//without options, unset() first tries to unset a var,
//if it fails it then tries to unset a function
//  Returns success unless an invalid option
//is given or a NAME is read-only
