/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:57:07 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/24 17:05:45 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if ((dst_len >= dstsize) || (dstsize == 0))
		return (src_len + dstsize);
	i = 0;
	while ((i + 1 + dst_len < dstsize) && src[i])
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	if (i + dst_len < dstsize)
		dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}
