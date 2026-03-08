/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:28:27 by smorlier          #+#    #+#             */
/*   Updated: 2025/08/13 14:36:55 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_args(const char *str)
{
	int	args_nb;

	args_nb = 0;
	while (*str)
	{
		if (*str == '%')
		{
			args_nb++;
			if (str[1] && str[1] == '%')
				str++;
		}
		str++;
	}
	return (args_nb);
}

int	print_arg(const char *str, va_list *lst)
{
	int	cnt;

	cnt = 0;
	if (*str == 'c')
		return (ut_putchar(va_arg(*lst, int)));
	if (*str == 's')
		return ((ut_putstr(va_arg(*lst, char *))));
	if (*str == 'd' || *str == 'i')
		return (putb((ssize_t)va_arg(*lst, int), "0123456789"));
	if (*str == 'u')
		return (putb((ssize_t)va_arg(*lst, unsigned int), "0123456789"));
	if (*str == 'p')
		return (ut_pt_ptr(va_arg(*lst, void *), "0123456789abcdef"));
	if (*str == 'x' )
		return (putb((ssize_t)va_arg(*lst, unsigned int), "0123456789abcdef"));
	if (*str == 'X' )
		return (putb((ssize_t)va_arg(*lst, unsigned int), "0123456789ABCDEF"));
	return (ut_putchar(*str));
}

int	loop_string(const char *str, va_list *lst)
{
	int		cnt;
	int		w_temp;

	cnt = 0;
	while (*str)
	{
		if (*str == '%')
		{
			if (!*(++str))
				return (cnt);
			w_temp = print_arg(str, lst);
			if (w_temp == -1)
				return (-1);
			cnt += w_temp;
		}
		else
		{
			if (ut_putchar(*str) == -1)
				return (-1);
			cnt++;
		}
		str++;
	}
	return (cnt);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	int		cnt;

	if (str == NULL)
		return (-1);
	cnt = write(1, "", 0);
	if (cnt < 0)
		return (-1);
	va_start(lst, str);
	cnt = loop_string(str, &lst);
	va_end(lst);
	return (cnt);
}
