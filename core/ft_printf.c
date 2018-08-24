/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 10:22:59 by besteba           #+#    #+#             */
/*   Updated: 2018/08/22 11:54:23 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_percent(const char **format)
{
	const char *tmp;

	tmp = *format;
	if (*tmp == '%' && *(tmp + 1) == '%')
		(*format)++;
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	form;
	int			i;

	i = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			reset_struct(&form);
			format++;
			handle_struct(&format, &form, args);
			i = form.ilenth;
		}
		else
		{
			print_percent(&format);
			write(1, &(*format), 1);
			format++;
			i++;
		}
	}
	va_end(args);
	return (i);
}
