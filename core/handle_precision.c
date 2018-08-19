/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:29:00 by besteba           #+#    #+#             */
/*   Updated: 2018/08/19 12:01:17 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_precision(t_format *form, char **tmp)
{
	char	*str;
	int		i;

	if (is_in_str("sS", form->specifier))
	{
		if (form->precision < ft_strlen(*tmp))
		{
			str = (char *)malloc(sizeof(char) * (ft_strlen(*tmp) + 1));
			i = 0;
			while (*(*tmp) && i < form->precision)
			{
				str[i] = *(*tmp);
				i++;
				(*tmp)++;
			}
			str[i] = '\0';
			*tmp = str;
			free(str);
		}
	}
	else
		padding_right(tmp, *tmp, form->precision, '0');
}
