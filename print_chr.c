/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 18:54:04 by besteba           #+#    #+#             */
/*   Updated: 2018/08/01 18:54:08 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void print_char(char c, int specifier)
{
	if (specifier == 1)
		c = (c >= 65 && c <= 90) ? c + 32 : c; // Lower case
	else if (specifier == 2)
		c = (c >= 97 && c <= 122) ? c - 32 : c; // Upper case
	write(1, &c, 1);
}
