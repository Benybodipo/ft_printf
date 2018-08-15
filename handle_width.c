/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 16:18:50 by besteba           #+#    #+#             */
/*   Updated: 2018/08/03 16:18:52 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char *padding_left(char *from, int width, char c)
{
	int i;
	char *str;

	i = 0;
	width = (width >= ft_strlen(from)) ? width : ft_strlen(from);
	str = malloc(sizeof(char) * (width + 1));

	while (i < (width - ft_strlen(from)))
	{
		str[i] = c;
		i++;
	}
	while (*from && i < width)
	{
		str[i] = *from;
		i++;
		from++;
	}
	str[i] = '\0';
	return (str);
}

static char *padding_rigth(char *from,  int width, char c)
{
	int i;
	char *str;

	i = 0;
	width = (width >= ft_strlen(from)) ? width : ft_strlen(from);
	str = malloc(sizeof(char) * (width + 1));
	while (*from)
	{
		str[i] = *from;
		i++;
		from++;
	}
	while (i < width)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char *padding(char *str, unsigned int width, char simbol, char c)
{
	int len;

	if (width <= ft_strlen(str))
		return (str);
	if (simbol == '-')
		return (padding_rigth(str,  width, c));
	return (padding_left(str, width, c));
}
