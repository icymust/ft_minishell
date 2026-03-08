/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:18 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/22 11:56:50 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (len == 0 || needle_len > ft_strlen(haystack) || needle_len > len)
		return (NULL);
	i = 0;
	while (haystack[i] && (i + needle_len <= len))
	{
		if (ft_strncmp(needle, &haystack[i], needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
