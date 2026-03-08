/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:01 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/18 15:38:03 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == ((const char) c))
			return ((char *) s);
		s++;
	}
	if (((char) c) == '\0')
		return ((char *) s);
	return (NULL);
}
