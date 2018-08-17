/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:09:33 by besteba           #+#    #+#             */
/*   Updated: 2018/08/17 12:09:34 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void handle_format(t_format *form, va_list ap)
{
	char *tmp;
	char *str;

	handle_length(ap, form, &tmp);
	if (form->precision)
		handle_precision(form, &tmp);
	str = tmp;
	if (!form->precision && form->flag == '0' && is_in_str("xXuUoOidD", form->specifier) && form->width)
		add_zero(&tmp, str, form);
	if ((is_in_str("#+", form->flag) || form->is_negative) && is_in_str("xXuUoOidD", form->specifier))
		add_prefix(&tmp, &str, form->specifier, form->is_negative);
	if (form->width && form->flag != '0')
		padding(&tmp, str, form->width, form->flag, ' ');
	if (form->flag == ' ' && is_in_str("xXuUoOpidD", form->specifier))
		write(1, " ", 1); //Create a function to add a space
	print_str(tmp, form->specifier);
	str = NULL;
}
