/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:08:45 by besteba           #+#    #+#             */
/*   Updated: 2018/08/17 12:08:47 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *pointer(char *pointer, t_format *form, int len)
{
	char *str;
	int i;
	int width;
	int precision;

	precision = (form->precision > len) ? form->precision : len;
	width = (form->width && !form->precision) ? form->width : precision;
	str =  malloc(sizeof(char) * (1 + len));
	str[0] = '0';
	str[1] = 'x';
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
void get_pointer(char **tmp, void *ptr, t_format *form)
{
	unsigned long	j;
	char		lst[16];
	char		*p;
	int len;

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
	if (form->flag == '0' && !form->precision)
		len = (ft_strlen(p) >= (form->width - 2)) ? ft_strlen(p) : (form->width - 2);
	else
		len = (form->precision > ft_strlen(p)) ? (form->precision + 2) : (ft_strlen(p) + 2);
	if (form->flag == '0')
		*tmp = pointer(p, form, len);
	if (is_in_str("+-", form->flag) || !form->flag)
		padding(tmp, pointer(p, form, len), form->width, form->flag, ' ');
}
