/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:58:13 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/22 22:53:00 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start_pos;
	size_t	end_pos;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(set) == 0 || ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	start_pos = 0;
	while (s1[start_pos] && ft_strchr(set, s1[start_pos]))
		start_pos++;
	end_pos = ft_strlen(s1) - 1;
	while (end_pos > start_pos && ft_strchr(set, s1[end_pos]))
		end_pos--;
	len = end_pos - start_pos + 1;
	if (len <= 0)
		return (ft_strdup(""));
	return (ft_substr(s1, start_pos, len));
}
