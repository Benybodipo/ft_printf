/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_printing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:21:53 by besteba           #+#    #+#             */
/*   Updated: 2018/08/19 15:37:43 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(char c, int specifier)
{
	if (is_in_str("SCDXUO", specifier) && (c >= 97 && c <= 122))
		c = c - 32;
	write(1, &c, 1);
}

void	print_str(char *str, int specifier)
{
	while (*str)
	{
		print_char(*str, specifier);
		str++;
	}
}
