/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wchart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besteba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 12:06:25 by besteba           #+#    #+#             */
/*   Updated: 2018/08/17 12:06:30 by besteba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

static int	wchar_utf8(wchar_t wc, char *convertion)
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

static int	ft_wchartochar(wchar_t wc)
{
	int		len;
	char	tab[4];

	len = wchar_utf8(wc, tab);
	return(tab[0]);
}

char	*ft_wstrtostr(wchar_t *wstr)
{
	char	*new;
	int		i;
	int		c;
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
