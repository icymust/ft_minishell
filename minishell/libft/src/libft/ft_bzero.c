/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:56:27 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/18 14:55:15 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t				i;
	unsigned char		*sign;

	sign = s;
	i = 0;
	while (i < n)
	{
		sign[i] = 0;
		i++;
	}
	return ;
}
