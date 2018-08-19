/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_zero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:57:30 by besteba           #+#    #+#             */
/*   Updated: 2018/08/19 11:37:50 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_zero(char **tmp, char *str, t_format *form)
{
	int		len;
	int		add_prefix;
	int		prefix_len;
	int		width;
	char	spec;

	prefix_len = 0;
	spec = form->specifier;
	if (is_in_str("xXoO", spec) && form->prefix == '#')
		add_prefix = 1;
	if (is_in_str("idD", spec) && (form->sign == '+' || form->is_negative))
		add_prefix = 1;
	if (is_in_str("xXoO", spec) && add_prefix)
		prefix_len = (is_in_str("xX", spec)) ? 2 : 1;
	if (is_in_str("idD", spec) && add_prefix)
		prefix_len = 1;
	len = ft_strlen(*tmp);
	width = form->width - prefix_len;
	if (width > len && !form->precision && spec != 'p')
		padding_right(tmp, str, width, '0');
	else if (width > len && form->precision && spec != 'p')
		padding_right(tmp, str, width, ' ');
}
