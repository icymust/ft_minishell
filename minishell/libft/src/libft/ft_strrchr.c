/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:21 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/22 22:59:55 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *) &s[len]);
	while (len > 0)
	{
		len--;
		if (s[len] == (const char) c)
			return ((char *) &s[len]);
	}
	return (NULL);
}
