/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 10:22:59 by besteba           #+#    #+#             */
/*   Updated: 2018/07/09 10:23:00 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_printf(const char* format, ...)
{
  va_list args;
	t_format form = {0};

  va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			format++;
			handle_struct(&format, &form, args);
		}
		else
			ft_putchar(*format);
		format++;
	}
  va_end(args);
}
