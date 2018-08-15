/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 12:28:08 by besteba           #+#    #+#             */
/*   Updated: 2018/08/07 12:28:11 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *ft_itoa_base(uintmax_t num, int base)
{
	char *number;
	uintmax_t tmp;
	int  len;

	if (base < 2 || base > 16)
		return (NULL);

	len = 1;
	tmp = num;
	while (tmp /= base)
		len++;

	if(!(number = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	return (number);
}
