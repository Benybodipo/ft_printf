/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_zero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:57:30 by besteba           #+#    #+#             */
/*   Updated: 2018/08/17 12:57:32 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void add_zero(char **tmp, char *str, t_format *form)
{
	int len;
	int add_prefix;
	int prefix_len;
	int width;

	prefix_len = 0;
	if (is_in_str("xXoO", form->specifier) && form->flag == '#')
		add_prefix = 1;
	if (is_in_str("idD", form->specifier) && (form->flag == '+' || form->is_negative))
		add_prefix = 1;
	if (is_in_str("xXoO", form->specifier) && add_prefix)
	 	prefix_len = (is_in_str("xX", form->specifier)) ? 2 : 1;
	if (is_in_str("idD", form->specifier) && add_prefix)
	 	prefix_len = 1;

	len = ft_strlen(*tmp);
	width = form->width - prefix_len;
	if (width > len && !form->precision && form->specifier != 'p')
		padding(tmp, str, width, form->flag, '0');
	else if (width > len && form->precision && form->specifier != 'p')
		padding(tmp, str, width, form->flag, ' ');
}
