/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preppend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:02:14 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 11:28:26 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*preppend(char *tmp, char *to_insert)
{
	char	*new;
	char	*str;
	int		len;
	int		i;

	str = ft_strdup(tmp);
	len = ft_strlen(str) + ft_strlen(to_insert);
	new = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*to_insert)
	{
		new[i] = *to_insert;
		i++;
		to_insert++;
	}
	while (*str)
	{
		new[i] = *str;
		str++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
