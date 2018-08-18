/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:31:10 by besteba           #+#    #+#             */
/*   Updated: 2018/08/18 12:19:15 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		padding_right(char **tmp, char *from, int width, char c)
{
	int		i;
	char	*str;
	char	*temp;

	i = 0;
	temp = ft_strdup(from);
	width = (width >= ft_strlen(from)) ? width : ft_strlen(from);
	str = malloc(sizeof(char) * (width + 1));
	while (i < (width - ft_strlen(from)))
	{
		str[i] = c;
		i++;
	}
	while (*temp && i < width)
	{
		str[i] = *temp;
		i++;
		temp++;
	}
	str[i] = '\0';
	*tmp = str;
	free(str);
}

static void		padding_left(char **tmp, char *from, int width, char c)
{
	int		i;
	char	*str;

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
	*tmp = str;
	free(str);
}

static void		padding(char **tmp, char *str, int width, char simbol, char c)
{
	int len;

	if (width <= ft_strlen(str))
		*tmp = str;
	else if (simbol == '-')
		padding_left(tmp, str, width, c);
	else if (!simbol || is_in_str("+#0 ", simbol))
		padding_right(tmp, str, width, c);
}
