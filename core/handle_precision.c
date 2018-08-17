/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:29:00 by besteba           #+#    #+#             */
/*   Updated: 2018/08/17 12:29:01 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void handle_precision(t_format *form, char **tmp)
{
	if (is_in_str("sS", form->specifier))
	{
		if (form->precision < ft_strlen(*tmp))
		{
			char *str;
			int i;

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
		padding(tmp, *tmp, form->precision, '+', '0');
}
