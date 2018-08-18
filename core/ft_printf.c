/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 10:22:59 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 11:44:00 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	form;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			reset_struct(&form);
			format++;
			handle_struct(&format, &form, args);
		}
		else
		{
			if (*format == '%' && *(format + 1) == '%')
				format++;
			write(1, &(*format), 1);
			format++;
		}
	}
	va_end(args);
}
