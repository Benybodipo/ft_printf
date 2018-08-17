/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 11:12:41 by besteba           #+#    #+#             */
/*   Updated: 2018/07/09 11:12:43 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdlib.h>
#include <limits.h>
# include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <wchar.h>

typedef struct format
{
	char flag;
	unsigned int width;
	unsigned int precision;
	char *length;
	char specifier;
	int is_negative;
} t_format;

/**************
	- LIBS -
***************/
int 		is_in_str(char *str,int c);
int 		is_digit(int c);
size_t 	ft_strlen(const char *str);

/**************
	- SRC -
***************/


#endif
