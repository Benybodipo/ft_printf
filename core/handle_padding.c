/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:31:10 by besteba           #+#    #+#             */
/*   Updated: 2018/08/19 15:32:54 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		padding_right(char **tmp, char *from, int width, char c)
{
	int		i;
	int		j;
	char	*str;
	char	*temp;

	i = 0;
	j = 0;
	temp = ft_strdup(from);
	width = (width >= (int)ft_strlen(from)) ? width : ft_strlen(from);
	str = malloc(sizeof(char) * (width + 1));
	while (i < (int)(width - ft_strlen(from)))
	{
		str[i] = c;
		i++;
	}
	while (temp[j] && i < width)
	{
		str[i] = temp[j];
		i++;
		j++;
	}
	str[i] = '\0';
	*tmp = ft_strdup(str);
	free(str);
}

void		padding_left(char **tmp, char *from, int width, char c)
{
	int		i;
	char	*str;

	i = 0;
	width = (width >= (int)ft_strlen(from)) ? width : (int)ft_strlen(from);
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
	*tmp = str;
	free(str);
}
