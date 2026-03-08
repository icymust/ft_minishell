/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:58:01 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/28 10:06:24 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*newstr(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (ft_substr(s, 0, len));
}

static void	free_on_fail(char **strs, int i)
{
	while (i--)
		free(strs[i]);
	free(strs);
}

static char	**fill_array(char **strs, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			strs[i] = newstr(s, c);
			if (strs[i] == NULL)
			{
				free_on_fail(strs, i);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	strs[i] = NULL;
	return (strs);
}

static size_t	count_strs(char const *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			return (counter);
		counter++;
		while (*s && *s != c)
			s++;
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = malloc((count_strs(s, c) + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs = fill_array(strs, s, c);
	return (strs);
}
