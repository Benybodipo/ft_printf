/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:12:25 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 12:52:40 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flags_slector(t_format *form, const char **str)
{
	char flag;
	char c;

	flag = 0;
	while (is_in_str("+-0# ", *(*str)))
	{
		c = *(*str);
		if (c == '+')
			flag = '+';
		else if (c == ' ' && flag != '+')
			flag = ' ';
		else if (c == '-')
			flag = '-';
		else if (c == '0' && flag != '-')
			flag = '0';
		else if (c == '#')
			flag = '#';
		(*str)++;
	}
	form->flag = flag;
}

char		*get_num(const char **str, int *dot)
{
	int		i;
	char	*tmp;

	i = 0;
	while (is_digit(*(*str)))
	{
		(*str)++;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	*str -= i;
	i = 0;
	while (is_digit(*(*str)))
	{
		tmp[i] = *(*str);
		(*str)++;
		if (*(*str) == '.')
			(*dot) = 1;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void		handle_struct(const char **format, t_format *form, va_list ap)
{
	int		percent;
	int		dot;
	char	*str;

	percent = 0;
	dot = 0;
	while (*(*format) && !form->specifier)
	{
		if (is_in_str("+-0 #", *(*format)))
			flags_slector(form, format);
		if (is_in_str(".", *(*format)))
			dot = 1;
		if (!dot && is_digit(*(*format)))
			form->width = (unsigned int)ft_atoi(get_num(&(*format), &dot));
		if (dot && is_digit(*(*format)))
			form->precision = (unsigned int)ft_atoi(get_num(&(*format), &dot));
		if (is_in_str("hljz", *(*format)) && !form->specifier)
			form->length = get_length(&(*format));
		if (is_in_str("sScCdDxXuUoOipb", *(*format)) && !form->specifier)
			form->specifier = *(*format);
		(*format)++;
	}
	handle_format(form, ap);
}

void		reset_struct(t_format *form)
{
	form->flag = 0;
	form->width = 0;
	form->precision = 0;
	form->length = 0;
	form->specifier = 0;
	form->is_negative = 0;
}
