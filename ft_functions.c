/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 12:28:31 by sasilves          #+#    #+#             */
/*   Updated: 2026/06/17 15:46:56 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_character(int c)
{
	char	ch;

	ch = (char)c;
	return (write(1, &ch, 1));
}

int	ft_print_string(char *str)
{
	int	count;

	if (!str)
		str = "(null)";
	count = 0;
	while (str[count])
	{
		ft_print_character(str[count]);
		count++;
	}
	return (count);
}

int	ft_print_base(unsigned long num, char format)
{
	char			*base;
	unsigned int	base_len;
	int				count;

	if (format == 'X')
	{
		base = "0123456789ABCDEF";
		base_len = 16;
	}
	else if (format == 'x')
	{
		base = "0123456789abcdef";
		base_len = 16;
	}
	else
	{
		base = "0123456789";
		base_len = 10;
	}
	count = 0;
	if (num >= base_len)
		count += ft_print_base(num / base_len, format);
	count += write(1, &base[num % base_len], 1);
	return (count);
}

int	ft_print_number(int n)
{
	long	l;
	int		count;

	l = n;
	count = 0;
	if (l < 0)
	{
		count += ft_print_character('-');
		l = -l;
	}
	count += ft_print_base((unsigned long)l, 'u');
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	if (!ptr)
		return (ft_print_string("(nil)"));
	count = ft_print_string("0x");
	count += ft_print_base((unsigned long)ptr, 'x');
	return (count);
}
