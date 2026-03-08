/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:57:40 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/28 09:57:38 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	i_str_len(int n)
{
	int				len;
	unsigned int	n_abs;

	n_abs = ((n >= 0) * n) - ((n < 0) * n);
	len = 2 + (n < 0);
	while ((n_abs / 10) > 0)
	{
		n_abs /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	n_abs;
	int				pos;

	n_abs = ((n >= 0) * n) - ((n < 0) * n);
	len = i_str_len(n);
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	pos = len - 1;
	str[pos] = '\0';
	if (n_abs == 0)
		str[0] = '0';
	while (pos > 0)
	{
		pos--;
		if (n < 0 && pos == 0)
			str[0] = '-';
		else
			str[pos] = (n_abs % 10) + '0';
		n_abs /= 10;
	}
	return (str);
}
