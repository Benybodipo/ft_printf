/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 11:57:30 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 11:23:13 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_uitoa_base(uintmax_t num, int base)
{
	int			len;
	char		*str;
	uintmax_t	tmp;

	len = 1;
	tmp = num;
	while (tmp /= base)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		tmp = num % base;
		str[len] = tmp + ((tmp > 9) ? ('a' - 10) : '0');
		num /= base;
	}
	return (str);
}
