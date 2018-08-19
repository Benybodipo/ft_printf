/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:08:45 by besteba           #+#    #+#             */
/*   Updated: 2018/08/19 15:36:56 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		allocate_mem_pointer(char **str, int len)
{
	*str = malloc(sizeof(char) * (1 + len));
	(*str)[0] = '0';
	(*str)[1] = 'x';
}

char		*pointer(char *pointer, t_format *form, int len)
{
	char	*str;
	size_t	i;
	int		width;
	int		precision;

	precision = ((int)form->precision > len) ? (int)form->precision : len;
	width = (form->width && !form->precision) ? form->width : precision;
	allocate_mem_pointer(&str, len);
	i = 2;
	if (form->flag == '0' || form->precision)
	{
		while (i < (width - ft_strlen(pointer)))
		{
			str[i] = '0';
			i++;
		}
	}
	while (*pointer)
	{
		str[i] = *pointer;
		pointer++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void		set_pointer_len(char **p, unsigned int *len, t_format *form)
{
	unsigned int	length;
	int				prec;

	length = ft_strlen(*p);
	prec = form->precision;
	if (form->flag == '0' && !prec)
		length = (length >= (form->width - 2)) ? length : (form->width - 2);
	else
		length = (prec > (int)length) ? (form->precision + 2) : (length + 2);
	*len = length;
}

void		get_pointer(char **tmp, void *ptr, t_format *form)
{
	unsigned long	j;
	char			lst[16];
	char			*p;
	unsigned int	len;

	j = (unsigned long)ptr;
	p = &lst[16];
	*p = '\0';
	while (p > lst)
	{
		--p;
		*p = "0123456789abcdef"[j % 16];
		j /= 16;
	}
	while (*p == '0')
		++p;
	set_pointer_len(&p, &len, form);
	if (form->flag == '0')
		*tmp = pointer(p, form, len);
	if (form->flag == '-')
		padding_left(tmp, pointer(p, form, len), form->width, ' ');
	else
		padding_right(tmp, pointer(p, form, len), form->width, ' ');
}
