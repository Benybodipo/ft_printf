/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:27:26 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 12:15:05 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t		get_unsigned_num(va_list args, t_format *form)
{
	uintmax_t num;

	num = va_arg(args, uintmax_t);
	if (!form->length)
		return (num);
	if (ft_strcmp(form->length, "hh"))
		num = (unsigned char)num;
	else if (ft_strcmp(form->length, "h"))
		num = (unsigned short int)num;
	else if (ft_strcmp(form->length, "l"))
		num = (unsigned long int)num;
	else if (ft_strcmp(form->length, "ll"))
		num = (unsigned long long int)num;
	else if (ft_strcmp(form->length, "j"))
		num = (uintmax_t)num;
	else if (ft_strcmp(form->length, "z"))
		num = (size_t)num;
	else
		num = (unsigned int)num;
	return (num);
}

intmax_t		get_signed_num(va_list args, t_format *form)
{
	intmax_t num;

	num = va_arg(args, intmax_t);
	if (!form->length)
		return (num);
	if (ft_strcmp(form->length, "hh"))
		num = (signed char)num;
	else if (ft_strcmp(form->length, "h"))
		num = (short int)num;
	else if (ft_strcmp(form->length, "l"))
		num = (long int)num;
	else if (ft_strcmp(form->length, "ll"))
		num = (long long int)num;
	else if (ft_strcmp(form->length, "j"))
		num = (intmax_t)num;
	else if (ft_strcmp(form->length, "z"))
		num = (size_t)num;
	else
		num = (int)num;
	return (num);
}

char			*get_length(const char **str)
{
	int		i;
	char	*len;

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

void			handle_is_negative(va_list ap, t_format *form, char **tmp)
{
	char spec;

	spec = form->specifier;
	*tmp = ft_itoa_base(get_signed_num(ap, form), get_base(spec));
	if (*(*tmp) == '-')
	{
		(*tmp)++;
		form->is_negative = 1;
	}
}

void			handle_length(va_list ap, t_format *form, char **tmp)
{
	char spec;
	char c[2];

	spec = form->specifier;
	if (is_in_str("dDi", spec))
		handle_is_negative(ap, form, tmp);
	else if (is_in_str("uoOxXb", spec))
		*tmp = ft_uitoa_base(get_signed_num(ap, form), get_base(spec));
	else if (is_in_str("p", spec))
		get_pointer(tmp, va_arg(ap, void *), form);
	else if (is_in_str("cC", spec))
	{
		if (ft_strcmp("l", form->length))
			c[0] = ft_wchartochar(va_arg(ap, wchar_t));
		else
			c[0] = ft_atoi(ft_uitoa_base(get_signed_num(ap, form), 10));
		c[1] = '\0';
		*tmp = c;
	}
	else if (is_in_str("sS", spec) && ft_strcmp(form->length, "l"))
		*tmp = ft_wstrtostr(va_arg(ap, wchar_t*));
	else
		*tmp = va_arg(ap, char *);
}
