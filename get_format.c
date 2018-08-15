/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 11:18:49 by besteba           #+#    #+#             */
/*   Updated: 2018/08/07 11:18:51 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *get_num(const char **str, int *dot)
{
	int  i;
	char *tmp;

	i = 0;
	while(is_digit(*(*str)))
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

char *get_length(const char **str)
{
	int i;
	int j;
	char *len;
	i = 0;
	while (is_in_str("hljz", *(*str)))
	{
		(*str)++;
		i++;
	}
	len = malloc(sizeof(char) * (i + 1));
	*str -= i;
	i = 0;
	while (is_in_str("hljz", *(*str)) && i < 2)
	{
		len[i] = *(*str);
		(*str)++;
		i++;
	}
	len[i] = '\0';
	return (len);
}

void handle_struct(const char **format, t_format *form, va_list ap)
{
	int percent;
	int dot;
	char *str;

	percent = 0;
	dot = 0;
	while (*(*format) && !form->specifier)
	{
		if (is_in_str("+-0 #", *(*format)))
			form->flag = *(*format);
		if (is_in_str(".", *(*format)))
			dot = 1;
		if (is_in_str("sScCdDxXuUoOip", *(*format)) && !form->specifier)
			form->specifier = *(*format);
		if (!dot && is_digit(*(*format)))
			form->width = (unsigned int)atoi(get_num(&(*format), &dot));
		if (dot && is_digit(*(*format)))
			form->precision = (unsigned int)atoi(get_num(&(*format), &dot));
		if (is_in_str("hljz", *(*format)) && !form->specifier)
			form->length = get_length(&(*format));
		(*format)++;
	}

}
