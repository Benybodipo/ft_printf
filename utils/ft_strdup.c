/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:37:22 by besteba           #+#    #+#             */
/*   Updated: 2018/08/17 12:37:24 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_strdup(const char *str)
{
	int i;
	char *new;

	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	i = -1;
	while (str[++i])
	{
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}
