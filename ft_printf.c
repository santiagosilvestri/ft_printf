/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:21:40 by sasilves          #+#    #+#             */
/*   Updated: 2026/06/17 10:21:32 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_set_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_print_character(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_string(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_number(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_base(va_arg(args, unsigned int), 'u'));
	else if (c == 'x' || c == 'X')
		return (ft_print_base(va_arg(args, unsigned int), c));
	if (c == '%')
		return (ft_print_character('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	if (!format)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += ft_set_format(format[i], args);
		}
		else
			count += ft_print_character(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
