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

#include "includes/ft_printf.h"

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
	const char *str;
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
	len = 0;
	while (str[len])
	{
		new[i] = str[len];
		len++;
		i++;
	}
	new[i] = '\0';
	return (new);
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

int		ft_atoi(char *str)
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
	// printf("%i\n", len);
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
	uintmax_t  tmp;

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

/*========= ADD ZERO ====================*/
void	add_zero(char **tmp, t_format *form)
{
	int		len; /*Think of remove*/
	int		add_prefix;
	int		prefix_len;
	int		width;
	char	spec;
	char  *str;

	prefix_len = 0;
	add_prefix = 0;
	str = ft_strdup(*tmp);
	spec = form->specifier;
	if (is_in_str("xXoO", spec) && form->prefix == '#')
		add_prefix = 1;
	if (is_in_str("idD", spec) && (form->sign == '+' || form->is_negative))
		add_prefix = 1;
	if (is_in_str("xXoO", spec) && add_prefix)
		prefix_len = (is_in_str("xX", spec)) ? 2 : 1;
	if (is_in_str("idD", spec) && add_prefix)
		prefix_len = 1;
	len = ft_strlen(*tmp);
	width = form->width - prefix_len;
	if (width > len && !form->precision && spec != 'p')
		padding_right(tmp, ft_strdup(*tmp), width, '0');
	else if (width > len && form->precision && spec != 'p')
		padding_right(tmp, ft_strdup(*tmp), width, ' ');
}
/*========= HANDLE FORMAT ====================*/
void	handle_format(t_format *form, va_list ap)
{
	char	*tmp = NULL;
	char	spe;
	int		prec;

	handle_length(ap, form, &tmp);
	spe = form->specifier;
	prec = form->precision;
	if (form->precision)
		handle_precision(form, &tmp);
	if (!prec && form->flag == 48 && is_in_str("xXuUoOidD", spe) && form->width)
		add_zero(&tmp, form);
	if (form->prefix || form->is_negative )
		handle_prefix(&tmp, form);
	if (form->width && form->width > (int)ft_strlen(tmp))
	{
		if (form->flag == '-')
			padding_left(&tmp, tmp, form->width, ' ');
		else
			padding_right(&tmp, tmp, form->width, ' ');
	}
	print_str(tmp, form);
	tmp = NULL;
}
/*========= HANDLE LENGTH ====================*/
uintmax_t		get_unsigned_num(va_list args, t_format *form)
{
	uintmax_t num;

	if (!form->length)
		return ((intmax_t)va_arg(args, unsigned int));
	if (ft_strcmp(form->length, "hh"))
		num = (intmax_t)va_arg(args, unsigned int);
	else if (ft_strcmp(form->length, "h"))
		num = (intmax_t)va_arg(args, int);
	else if (ft_strcmp(form->length, "l"))
		num = (intmax_t)va_arg(args, unsigned long int);
	else if (ft_strcmp(form->length, "ll"))
		num = (intmax_t)va_arg(args, unsigned long long int);
	else if (ft_strcmp(form->length, "j"))
		num = va_arg(args, uintmax_t);
	else if (ft_strcmp(form->length, "z"))
		num = (intmax_t)va_arg(args, size_t);
	else
		num = (intmax_t)va_arg(args, unsigned int);
	return (num);
}

intmax_t		get_signed_num(va_list args, t_format *form)
{
	intmax_t num;

	if (!form->length)
		return ((intmax_t)va_arg(args, int));
	if (ft_strcmp(form->length, "hh"))
		num = (intmax_t)va_arg(args, signed int);
	else if (ft_strcmp(form->length, "h"))
		num = (intmax_t)va_arg(args, int);
	else if (ft_strcmp(form->length, "l"))
		num = (intmax_t)va_arg(args, long int);
	else if (ft_strcmp(form->length, "ll"))
		num = (intmax_t)va_arg(args, long long int);
	else if (ft_strcmp(form->length, "j"))
		num = va_arg(args, intmax_t);
	else if (ft_strcmp(form->length, "z"))
		num = (intmax_t)va_arg(args, size_t);
	else
		num = (intmax_t)va_arg(args, int);

	return (num);
}


void			handle_is_negative(va_list ap, t_format *form, char **tmp)
{
	char spec;

	spec = form->specifier;
	*tmp = ft_itoa_base(get_signed_num(ap, form), get_base(spec));

	if (ft_atoi(*tmp) < 0)
	{
		*tmp = ft_itoa_base((ft_atoi(*tmp) * -1), get_base(spec));
		form->is_negative = 1;
	}
}

void			handle_length(va_list ap, t_format *form, char **tmp)
{
	char spec;
	char c[2];
	char *length;

	spec = form->specifier;
	length = form->length;
	if (is_in_str("dDi", spec))
		handle_is_negative(ap, form, tmp);
	else if (is_in_str("uUoOxXb", spec))
		*tmp = ft_uitoa_base(get_unsigned_num(ap, form), get_base(spec));
	else if (is_in_str("p", spec))
		get_pointer(tmp, va_arg(ap, void *), form);
	else if (is_in_str("cC", spec))
	{
		if (length && ft_strcmp("l", length))
			c[0] = ft_wchartochar(va_arg(ap, int));
		else
			c[0] = ft_atoi(ft_uitoa_base(get_signed_num(ap, form), 10));
		c[1] = '\0';
		*tmp = ft_strdup(c);
	}
	else if (length && is_in_str("sS", spec) && ft_strcmp(length, "l"))
		*tmp = ft_wstrtostr(va_arg(ap, wchar_t*));
	else if (is_in_str("sS", spec) && !length)
		*tmp = va_arg(ap, char *);
}

/*========= HANDLE PADDING ====================*/
void		padding_right(char **tmp, char *from, int width, char c)
{
	int		i;
	int		j;
	char	*str;
	char	*temp;

	i = 0;
	j = 0;
	temp = ft_strdup(from);
	width = (width >= (int)ft_strlen(from)) ? width : (int)ft_strlen(from);
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
	char *temp;

	i = 0;
	temp = ft_strdup(from);
	width = (width >= (int)ft_strlen(from)) ? width : (int)ft_strlen(from);
	str = malloc(sizeof(char) * (width + 1));
	while (temp[i])
	{
		str[i] = temp[i];
		i++;
		from++;
	}
	while (i < width)
	{
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	*tmp = ft_strdup(str);
	free(str);
}

/*========= HANDLE POINTERS ====================*/
void		allocate_mem_pointer(char **str, int len)
{
	*str = malloc(sizeof(char) * (1 + len));
	(*str)[0] = '0';
	(*str)[1] = 'x';
}

char		*pointer(char *pointer, t_format *form, int len)
{
	char	*str;
	size_t	i;
	int		width;
	int		precision;

	precision = ((int)form->precision > len) ? (int)form->precision : len;
	width = (form->width && !form->precision) ? form->width : precision;
	allocate_mem_pointer(&str, len);
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

void		set_pointer_len(char **p, unsigned int *len, t_format *form)
{
	unsigned int	length;
	int				prec;

	length = ft_strlen(*p);
	prec = form->precision;
	if (form->flag == '0' && !prec)
		length = (length >= (form->width - 2)) ? length : (form->width - 2);
	else
		length = (prec > (int)length) ? (form->precision + 2) : (length + 2);
	*len = length;
}

void		get_pointer(char **tmp, void *ptr, t_format *form)
{
	unsigned long	j;
	char			lst[16];
	char			*p;
	unsigned int	len;

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
	set_pointer_len(&p, &len, form);
	if (form->flag == '0')
		*tmp = pointer(p, form, len);
	if (form->flag == '-')
		padding_left(tmp, pointer(p, form, len), form->width, ' ');
	else
		padding_right(tmp, pointer(p, form, len), form->width, ' ');
}
/*========= HANDLE PRECISION ====================*/
void	handle_precision(t_format *form, char **tmp)
{
	char			*str;
	unsigned int	i;

	if (is_in_str("sS", form->specifier))
	{
		if (form->precision < ft_strlen(*tmp))
		{
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
		padding_right(tmp, *tmp, form->precision, '0');
}
/*========= HANDLE PREFIX ====================*/
int		get_base(char c)
{
	if (is_in_str("xX", c))
		return (16);
	else if (is_in_str("oO", c))
		return (8);
	else if (is_in_str("b", c))
		return (2);
	return (10);
}

char *add_prefix(char *tmp, t_format *form)
{
	char	*prefix;
	char	spec;
	int		is_negative;

	spec = form->specifier;
	is_negative = form->is_negative;
	if (spec == 'x' || spec == 'X')
		prefix = "0x";
	else if (spec == 'o' || spec == 'O')
		prefix = "0";
	else if (is_in_str("idD", spec) && is_negative)
		prefix = "-";
	else if (!is_negative && is_in_str("idD", spec) && form->sign == ' ')
		prefix = " ";
	else if (!is_negative && is_in_str("idD", spec) && form->sign == '+')
		prefix = "+";
	return (preppend(ft_strdup(tmp), prefix));
}

void handle_prefix(char **tmp, t_format *form)
{
	char spe;

	spe = form->specifier;
	if (form->prefix && is_in_str("xXoO", form->specifier))
		*tmp = add_prefix(*tmp, form);
	if (form->sign && is_in_str("idD", spe) && !form->is_negative)
		*tmp = add_prefix(*tmp, form);
	if (form->is_negative && is_in_str("idD", spe))
		*tmp = preppend(*tmp, "-");
}

/*========= HANDLE PRINTING ====================*/
void	print_char(char c, int specifier)
{
	if (is_in_str("SCDXUO", specifier) && (c >= 97 && c <= 122))
		c = c - 32;
	write(1, &c, 1);
}

void	print_str(char *str, t_format *form)
{
	while (*str)
	{
		print_char(*str, form->specifier);
		form->ilenth++;
		str++;
	}
}

/*========= HANDLE STRUCT ====================*/
void		flags_slector(t_format *form, const char **str)
{
	char c;

	while (is_in_str("+-0# ", *(*str)) && *(*str))
	{
		c = *(*str);
		if (c == '+')
			form->sign = '+';
		else if (c == ' ' && form->sign != '+')
			form->sign = ' ';
		else if (c == '-')
			form->flag = '-';
		else if (c == '0' && form->flag != '-')
			form->flag = '0';
		else if (c == '#')
			form->prefix = '#';
		(*str)++;
	}
}

char		*get_num(const char **str, int *dot)
{
	int		i;
	char	*tmp;

	i = 0;
	while (is_digit(*(*str)))
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

void		handle_struct(const char **format, t_format *form, va_list ap)
{
	int		percent;
	int		dot;

	percent = 0;
	dot = 0;
	while (*(*format) && (*(*format) + 1) != '%' && !form->specifier)
	{
		if (is_in_str("+-0 #", *(*format)))
			flags_slector(form, format);
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
	if (form->specifier)
		handle_format(form, ap);
}

void		reset_struct(t_format *form)
{
	form->flag = 0;
	form->sign = 0;
	form->prefix = 0;
	form->width = 0;
	form->precision = 0;
	form->length = 0;
	form->ilenth = 0;
	form->specifier = 0;
	form->is_negative = 0;
}
/*========= HANDLE WCHART ====================*/
int		wchar_utf8(wchar_t wc, char *convertion)
{
	int		len;

	len = 0;
	if (wc <= 0xFF)
		convertion[len++] = wc;
	else if (wc < 0x0800)
	{
		convertion[len++] = ((wc >> 6) & 0x1F) | 0xC0;
		convertion[len++] = ((wc >> 0) & 0x3F) | 0x80;
	}
	else if (wc < 0x010000)
	{
		convertion[len++] = ((wc >> 12) & 0x0F) | 0xE0;
		convertion[len++] = ((wc >> 6) & 0x3F) | 0x80;
		convertion[len++] = ((wc >> 0) & 0x3F) | 0x80;
	}
	else if (wc < 0x110000)
	{
		convertion[len++] = ((wc >> 18) & 0x07) | 0xF0;
		convertion[len++] = ((wc >> 12) & 0x3F) | 0x80;
		convertion[len++] = ((wc >> 6) & 0x3F) | 0x80;
		convertion[len++] = ((wc >> 0) & 0x3F) | 0x80;
	}
	return (len);
}

int		ft_wchartochar(wchar_t wc)
{
	int		len;
	char	tab[4];

	len = wchar_utf8(wc, tab);
	return (tab[0]);
}

char	*ft_wstrtostr(wchar_t *wstr)
{
	char	*new;
	int		i;
	int		len;

	if (!wstr)
		return (0);
	i = 0;
	len = ft_wbytelen(wstr);
	if (!(new = (char*)malloc(len + 1 * (sizeof(char)))))
		return (NULL);
	new[len] = '\0';
	while (wstr && *wstr)
	{
		new[i] = ft_wchartochar(*wstr);
		i++;
		wstr++;
	}
	return (new);
}

/*========= HANDLE WCHART_LEN ====================*/
int			ft_wcharlen(wchar_t wchar)
{
	if (wchar <= 0x7f)
		return (1);
	else if (wchar <= 0x7ff)
		return (2);
	else if (wchar <= 0xffff)
		return (3);
	else
		return (4);
}

size_t		ft_wstrlen(wchar_t *ws)
{
	size_t	len;

	len = 0;
	if (!ws)
		return (0);
	while (*(ws++))
		len++;
	return (len);
}

size_t		ft_wbytelen(wchar_t *ws)
{
	size_t	len;
	size_t	bytelen;

	len = ft_wstrlen(ws);
	bytelen = 0;
	while (len > 0)
	{
		bytelen += ft_wcharlen(*ws);
		ws++;
		len--;
	}
	return (bytelen);
}
/*========= FT PRINTF ==================*/

void	print_percent(const char **format)
{
	const char *tmp;

	tmp = *format;
	if (*tmp == '%' && *(tmp + 1) == '%')
		(*format)++;
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	t_format	form;
	int			i;

	i = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1) != '%')
		{

			reset_struct(&form);
			format++;
			handle_struct(&format, &form, args);
			i = form.ilenth;
			printf("|%c|", form.specifier);
		}
		else
		{
			print_percent(&format);
			write(1, &(*format), 1);
			format++;
			i++;
		}
	}
	va_end(args);
	return (i);
}

int	main()
{
	int neg = -3400;
	int pos = 345;
	char *str = "Hello";



	// ft_printf("Hello %i my %s friend", 65, "you");
	ft_printf("num %i\n", 67);

	return(0);
}
