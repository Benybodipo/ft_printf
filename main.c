/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 17:31:19 by besteba           #+#    #+#             */
/*   Updated: 2018/08/03 17:31:26 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// void add_prefix(char **tmp, char **str, char spec);
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

char *preppend(char *tmp, char *to_insert)
{
	char *new;
	char *str;
	int len;
	int i;


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

static void print_char(char c, int specifier)
{
	if (is_in_str("scdxuoipb", specifier) && (c >= 65 && c <= 90))
		c =  c + 32; // Lower case
	else if (is_in_str("SCDXUO", specifier) && (c >= 97 && c <= 122))
		c =  c - 32; // Upper case
	write(1, &c, 1);
}

static void print_str(char *str, int specifier)
{
	while (*str)
	{
		print_char(*str, specifier);
		str++;
	}
}
static void padding_right(char **tmp, char *from, int width, char c)
{
	int i;
	char *str;
	char *temp;

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

static void padding_left(char **tmp, char *from, int width, char c)
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
	*tmp = str;
	free(str);
}

static void padding(char **tmp, char *str, unsigned int width, char simbol, char c)
{
	int len;

	if (width <= ft_strlen(str))
		*tmp = str;
	else if (simbol == '-')
		padding_left(tmp, str,  width, c);
	else if (!simbol || is_in_str("+#0 ", simbol))
		padding_right(tmp, str,  width, c);
}
int ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	if (*str1 || *str2)
		return (0);
	return (1);
}

size_t ft_strlen(const char *str)
{
	int len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

int is_digit(int c)
{
	return ((c >= 48 && c <= 57) ? 1 : 0);
}

int is_in_str(char *str,int c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char *get_num(const char **str, int *dot)
{
	int  i;
	char *tmp;

	i = 0;
	while(is_digit(*(*str)))
	{
		(*str)++;
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (i + 1));
	*str -= i;
	i = 0;
	while (is_digit(*(*str)))
	{
		tmp[i] = *(*str);
		(*str)++;
		if (*(*str) == '.')
			(*dot) = 1;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char *get_length(const char **str)
{
	int i;
	int j;
	char *len;
	i = 0;
	while (is_in_str("hljz", *(*str)))
	{
		(*str)++;
		i++;
	}
	len = malloc(sizeof(char) * (i + 1));
	*str -= i;
	i = 0;
	while (is_in_str("hljz", *(*str)) && i < 2)
	{
		len[i] = *(*str);
		(*str)++;
		i++;
	}
	len[i] = '\0';
	return (len);
}

char *ft_itoa_base(int num, int base)
{
	int len;
	char *str;
	long long value;
	char *tab;

	tab = "0123456789abcdef";
	value = num;
	len = (value < 0 && base == 10) ? 1 : 0;
	value = (value < 0) ? (-1 * value) : value;
	while (value /= base)
		len++;
	value = num;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if(value < 0 && base == 10)
		str[0] = '-';
	if (value < 0)
		value = value * -1;
	while(value > 0)
	{
		str[len] = tab[value % base];
		value /= base;
		len--;
	}
	return (str);
}
char *ft_uitoa_base(uintmax_t num, int base)
{
	int len;
	char *str;
	uintmax_t tmp;

	len = 1;
	tmp = num;
	while (tmp /= base)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);

	str[len] = '\0';
	while(len-- > 0)
	{
		tmp =  num % base;
		str[len] = tmp + ((tmp > 9) ? ('a' - 10) : '0');
		num /= base;
	}
	return (str);
}

uintmax_t get_unsigned_num(va_list args, t_format *form)
{
	uintmax_t num;

	num = va_arg(args, uintmax_t);
	if (!form->length)
		return (num);
	if (ft_strcmp(form->length, "hh"))
		num = (unsigned char)num;
	else if (ft_strcmp(form->length, "h"))
		num = (unsigned short int)num;
	else if (ft_strcmp(form->length, "l"))
		num = (unsigned long int )num;
	else if (ft_strcmp(form->length, "ll"))
		num = (unsigned long long int)num;
	else if (ft_strcmp(form->length, "j"))
		num = (uintmax_t)num;
	else if (ft_strcmp(form->length, "z"))
		num = (size_t)num;
	else
		num = (unsigned int)num;
	return (num);
}

intmax_t get_signed_num(va_list args, t_format *form)
{
	intmax_t num;

	num = va_arg(args, intmax_t);
	if (!form->length)
		return (num);
	if (ft_strcmp(form->length, "hh"))
		num = (signed char)num;
	else if (ft_strcmp(form->length, "h"))
		num = (short int)num;
	else if (ft_strcmp(form->length, "l"))
		num = (long int )num;
	else if (ft_strcmp(form->length, "ll"))
		num = (long long int)num;
	else if (ft_strcmp(form->length, "j"))
		num = (intmax_t)num;
	else if (ft_strcmp(form->length, "z"))
		num = (size_t)num;
	else
		num = (int)num;
	return (num);
}

int ft_atoi(char *str)
{
	int				i;
	long long int	result;
	long long int	neg;

	i = 0;
	neg = 1;
	result = 0;
	while (is_in_str("\n\t\v\f\r ", str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < 48 || 57 < str[i])
			return (result * neg);
		else
			result = (result * 10) + (long long int)(str[i] - '0');
		i++;
	}
	return (result * neg);
}

int get_base(char c)
{
	if (is_in_str("xX", c))
		return (16);
	else if (is_in_str("oO", c))
		return (8);
	else if (is_in_str("b", c))
		return (2);
	return (10);
}

char *pointer(char *pointer, t_format *form, int len)
{
	char *str;
	int i;
	int width;
	int precision;

	precision = (form->precision > len) ? form->precision : len;
	width = (form->width && !form->precision) ? form->width : precision;
	str =  malloc(sizeof(char) * (1 + len));
	str[0] = '0';
	str[1] = 'x';
	i = 2;
	if (form->flag == '0' || form->precision)
	{
		while (i < (width - ft_strlen(pointer)))
		{
			str[i] = '0';
			i++;
		}
	}
	while (*pointer)
	{
		str[i] = *pointer;
		pointer++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
void get_pointer(char **tmp, void *ptr, t_format *form)
{
	unsigned long	j;
	char		lst[16];
	char		*p;
	int len;

	j = (unsigned long)ptr;
	p = &lst[16];
	*p = '\0';
	while (p > lst)
	{
		--p;
		*p = "0123456789abcdef"[j % 16];
		j /= 16;
	}
	while (*p == '0')
		++p;
	if (form->flag == '0' && !form->precision)
		len = (ft_strlen(p) >= (form->width - 2)) ? ft_strlen(p) : (form->width - 2);
	else
		len = (form->precision > ft_strlen(p)) ? (form->precision + 2) : (ft_strlen(p) + 2);
	if (form->flag == '0')
		*tmp = pointer(p, form, len);
	if (is_in_str("+-", form->flag) || !form->flag)
		padding(tmp, pointer(p, form, len), form->width, form->flag, ' ');
}

void handle_length(va_list ap, t_format *form, char **tmp)
{
	char spec;
	char *len;
	char c[2];

	spec = form->specifier;
	if (is_in_str("dDi",  spec))
	{
		*tmp = ft_itoa_base(get_signed_num(ap, form), get_base(form->specifier));
		if (*(*tmp) == '-')
		{
			(*tmp)++;
			form->is_negative = 1;
		}
	}
	else if (is_in_str("uoOxXb", spec))
		*tmp = ft_uitoa_base(get_signed_num(ap, form), get_base(form->specifier));
	else if (is_in_str("p", spec))
		get_pointer(tmp, va_arg(ap, void *), form);
	else if (is_in_str("c", spec))
	{
		c[0] = ft_atoi(ft_uitoa_base(get_signed_num(ap, form), 10));
		c[1] = '\0';
		*tmp = c;
	}
	else
		*tmp = va_arg(ap, char *);
}

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

void add_prefix(char **tmp, char **str, char spec, int is_negative)
{
  char *prefix;
	char *temp;

	temp = ft_strdup(*tmp);
  if (spec == 'x' || spec == 'X')
    prefix = "0x";
  else if (spec == 'o' || spec == 'O')
    prefix = "0";
	else if (is_in_str("idD", spec) && is_negative)
		prefix = "-";
	else
		prefix = "+";
	*tmp = preppend(temp, prefix);
	*str = preppend(temp, prefix); // Be aware
}

void add_zero(char **tmp, char *str, t_format *form)
{
	int len;
	int add_prefix;
	int prefix_len;
	int width;

	prefix_len = 0;
	if (is_in_str("xXoO", form->specifier) && form->flag == '#')
		add_prefix = 1;
	if (is_in_str("idD", form->specifier) && (form->flag == '+' || form->is_negative))
		add_prefix = 1;
	if (is_in_str("xXoO", form->specifier) && add_prefix)
	 	prefix_len = (is_in_str("xX", form->specifier)) ? 2 : 1;
	if (is_in_str("idD", form->specifier) && add_prefix)
	 	prefix_len = 1;

	len = ft_strlen(*tmp);
	width = form->width - prefix_len;
	if (width > len && !form->precision && form->specifier != 'p')
		padding(tmp, str, width, form->flag, '0');
	else if (width > len && form->precision && form->specifier != 'p')
		padding(tmp, str, width, form->flag, ' ');
}

void handle_format(t_format *form, va_list ap)
{
	char *tmp;
	char *str;

	handle_length(ap, form, &tmp);
	if (form->precision)
		handle_precision(form, &tmp);
	str = tmp;
	if (!form->precision && form->flag == '0' && is_in_str("xXuUoOidD", form->specifier) && form->width)
		add_zero(&tmp, str, form);
	if ((is_in_str("#+", form->flag) || form->is_negative) && is_in_str("xXuUoOidD", form->specifier))
		add_prefix(&tmp, &str, form->specifier, form->is_negative);
	if (form->width && form->flag != '0')
		padding(&tmp, str, form->width, form->flag, ' ');
	if (form->flag == ' ' && is_in_str("xXuUoOpidD", form->specifier))
		write(1, " ", 1);
	print_str(tmp, form->specifier);
	str = NULL;
}
void handle_struct(const char **format, t_format *form, va_list ap)
{
	int percent;
	int dot;
	char *str;

	percent = 0;
	dot = 0;
	while (*(*format) && !form->specifier)
	{
		if (is_in_str("+-0 #", *(*format)))
		{
			form->flag = *(*format);
		}
		if (is_in_str(".", *(*format)))
			dot = 1;
		if (!dot && is_digit(*(*format)))
			form->width = (unsigned int)ft_atoi(get_num(&(*format), &dot));
		if (dot && is_digit(*(*format)))
			form->precision = (unsigned int)ft_atoi(get_num(&(*format), &dot));
		if (is_in_str("hljz", *(*format)) && !form->specifier)
			form->length = get_length(&(*format));
		if (is_in_str("sScCdDxXuUoOipb", *(*format)) && !form->specifier)
			form->specifier = *(*format);
		(*format)++;
	}
	handle_format(form, ap);
}

void reset_struct(t_format *form)
{
	form->flag = 0;
	form->width = 0;
	form->precision = 0;
	form->length = 0;
	form->specifier = 0;
	form->is_negative = 0;
}

void ft_printf(const char* format, ...)
{
  va_list args;
	t_format form;

  va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{
			reset_struct(&form);
			format++;
			handle_struct(&format, &form, args);
		}
		else
		{
			if(*format == '%' && *(format + 1) == '%')
				format++;
			write(1, &(*format), 1);
			format++;
		}
	}
  va_end(args);
}

int	main()
{
	int num = -34563626;

	ft_printf("|%-012i|\n", num);
	printf("|%-012i|\n", num);
	return(0);
}
