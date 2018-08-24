/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:20:03 by besteba           #+#    #+#             */
/*   Updated: 2018/08/22 11:46:17 by besteba          ###   ########.fr       */
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

char	*add_prefix(char *tmp, t_format *form)
{
	char	*prefix;
	char	spec;
	int		is_negative;

	spec = form->specifier;
	prefix = NULL;
	is_negative = form->is_negative;
	if (spec == 'x' || spec == 'X')
		prefix = "0x";
	else if (spec == 'o' || spec == 'O')
		prefix = "0";
	else if (is_in_str("idD", spec) && is_negative)
		prefix = "-";
	else if (!is_negative && is_in_str("idD", spec) && form->sign == ' ')
		prefix = " ";
	else if (!is_negative && is_in_str("idD", spec) && form->sign == '+')
		prefix = "+";
	return (preppend(ft_strdup(tmp), prefix));
}

void	handle_prefix(char **tmp, t_format *form)
{
	char spe;

	spe = form->specifier;
	if (form->prefix && is_in_str("xXoO", form->specifier))
		*tmp = add_prefix(*tmp, form);
	if (form->sign && is_in_str("idD", spe) && !form->is_negative)
		*tmp = add_prefix(*tmp, form);
	if (form->is_negative && is_in_str("idD", spe))
		*tmp = preppend(*tmp, "-");
}
