/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbardett <mbardett@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:21:50 by mbardett          #+#    #+#             */
/*   Updated: 2023/03/22 23:21:51 by mbardett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../global.h"

//without options, unset() first tries to unset a var,
//if it fails it then tries to unset a function
//  Returns success unless an invalid option
//is given or a NAME is read-only
