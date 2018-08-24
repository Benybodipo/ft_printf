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
	char	spe;
	int		prec;

	handle_length(ap, form, &tmp);
	spe = form->specifier;
	prec = form->precision;
	if (form->precision)
		handle_precision(form, &tmp);
	if (!prec && form->flag == 48 && is_in_str("xXuUoOidD", spe) && form->width)
		add_zero(&tmp, form);
	handle_prefix(&tmp, form);
	if (form->width && form->flag == '-')
	{
		if (form->flag == '-')
			padding_left(&tmp, tmp, form->width, ' ');
		else
			padding_right(&tmp, tmp, form->width, ' ');
	}
	print_str(tmp, form);
	tmp = NULL;
}
