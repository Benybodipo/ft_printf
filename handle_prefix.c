/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 11:50:06 by besteba           #+#    #+#             */
/*   Updated: 2018/08/05 11:50:08 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *add_prefix(char *arg, char spec)
{
  int i;
  char *str;
  char *prefix;

  if (spec == 'x' || spec == 'X')
    prefix = "0x";
  else if (spec == 'o' || spec == 'O')
    prefix = "0";

  str =  malloc(sizeof(char) * (get_strlen(arg) + get_strlen(prefix) + 1));

  i = 0;
  while (*prefix)
  {
    str[i] = *prefix;
    prefix++;
    i++;
  }
  while (*arg)
  {
    str[i] = *arg;
    arg++;
    i++;
  }
  str[i] = '\0';
  return  (str);
}
