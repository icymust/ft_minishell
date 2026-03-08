/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:56:47 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/24 15:42:02 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	if (n == 0)
		return (NULL);
	while (n)
	{
		if (*ptr == (unsigned char) c)
			return ((void *)ptr);
		n--;
		ptr++;
	}
	return (NULL);
}
