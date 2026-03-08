/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:57:58 by smorlier          #+#    #+#             */
/*   Updated: 2025/08/13 14:37:09 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ut_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ut_putstr(char *str)
{
	if (str == NULL)
		return (ut_putstr("(null)"));
	return (write(1, str, ut_strlen(str)));
}

int	putb(ssize_t n, char *base)
{
	size_t	number;
	int		w_count;
	size_t	base_len;
	int		w_temp;

	w_count = 0;
	base_len = ut_strlen(base);
	number = n;
	if (n < 0)
	{
		number = -n;
		if (ut_putchar('-') == -1)
			return (-1);
		w_count++;
	}
	if (number < base_len)
		return (w_count + ut_putchar(base[number]));
	w_temp = putb((number / base_len), base);
	if (w_temp == -1)
		return (-1);
	w_count += w_temp;
	if (ut_putchar(base[number % base_len]) == -1)
		return (-1);
	w_count++;
	return (w_count);
}

int	ut_pt_ptr(void *ptr, char *base)
{
	size_t	number;
	int		w_count;
	size_t	base_len;
	int		w_temp;

	if (ut_putstr("0x") == -1)
		return (-1);
	w_count = 2;
	base_len = ut_strlen(base);
	number = (size_t) ptr;
	if (number < base_len)
		return (w_count + ut_putchar(base[number]));
	w_temp = putb((number / base_len), base);
	if (w_temp == -1)
		return (-1);
	w_count += w_temp;
	if (ut_putchar(base[number % base_len]) == -1)
		return (-1);
	w_count++;
	return (w_count);
}

size_t	ut_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}
