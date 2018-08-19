/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:09:33 by besteba           #+#    #+#             */
/*   Updated: 2018/08/19 11:42:38 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_format(t_format *form, va_list ap)
{
	char	*tmp;
	char	*str;
	char	spe;
	int		prec;

	handle_length(ap, form, &tmp);
	spe = form->specifier;
	prec = form->precision;
	if (form->precision)
		handle_precision(form, &tmp);
	str = tmp;
	if (!prec && form->flag == 48 && is_in_str("xXuUoOidD", spe) && form->width)
		add_zero(&tmp, str, form);
	if (form->prefix && is_in_str("xXoO", form->specifier))
		add_prefix(&tmp, &str, form);
	if (form->sign && is_in_str("idD", spe) && !form->is_negative)
		add_prefix(&tmp, &str, form);
	if (form->flag && form->is_negative && is_in_str("idD", spe))
		add_prefix(&tmp, &str, form);
	if (form->width && form->flag == '-')
		padding_left(&tmp, str, form->width, ' ');
	else
		padding_right(&tmp, str, form->width, ' ');
	print_str(tmp, form->specifier);
	str = NULL;
}
