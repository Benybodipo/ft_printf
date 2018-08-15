/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:17:49 by besteba           #+#    #+#             */
/*   Updated: 2018/08/03 16:18:01 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *str_precision(char *str, int max)
{
	int len;
	int i;
	char *new_str;

	len = (int)ft_strlen(str);
	new_str = malloc(sizeof(char) * (max + 1));
	while (i < max && i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
