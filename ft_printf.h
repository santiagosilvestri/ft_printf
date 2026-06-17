/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:46:48 by sasilves          #+#    #+#             */
/*   Updated: 2026/06/17 10:12:30 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_print_character(int c);
int	ft_print_string(char *str);
int	ft_print_base(unsigned long num, char format);
int	ft_print_number(int n);
int	ft_print_pointer(void *ptr);

#endif