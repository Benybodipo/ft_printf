/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:20:03 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 12:47:57 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_base(char c)
{
	if (is_in_str("xX", c))
		return (16);
	else if (is_in_str("oO", c))
		return (8);
	else if (is_in_str("b", c))
		return (2);
	return (10);
}

void	add_prefix(char **tmp, char **str, char spec, int is_negative)
{
	char *prefix;
	char *temp;

	temp = ft_strdup(*tmp);
	if (spec == 'x' || spec == 'X')
		prefix = "0x";
	else if (spec == 'o' || spec == 'O')
		prefix = "0";
	else if (is_in_str("idD", spec) && is_negative)
		prefix = "-";
	else
		prefix = "+";
	*tmp = preppend(temp, prefix);
	*str = preppend(temp, prefix);
}
