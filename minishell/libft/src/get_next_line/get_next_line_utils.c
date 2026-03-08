/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:55:13 by smorlier          #+#    #+#             */
/*   Updated: 2025/08/07 15:34:12 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ut_memcpy(void *dst, const void *src, ssize_t n)
{
	ssize_t				i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	if (!dst && !src)
		return (NULL);
	ptr_dest = dst;
	ptr_src = src;
	i = 0;
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

void	*ut_memmove(void *dst, const void *src, ssize_t len)
{
	ssize_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src && len != 0)
		return (NULL);
	d = dst;
	s = src;
	if (d < s)
		ut_memcpy(dst, src, len);
	else if (d > s)
	{
		i = len;
		while (i > 0)
		{
			i--;
			d[i] = s[i];
		}
	}
	return (dst);
}

void	ut_clean_buffer(char *buffer, ssize_t size)
{
	ssize_t			i;

	i = 0;
	while (i < size)
	{
		buffer[i] = 0;
		i++;
	}
	return ;
}

int	ut_nl_in(t_buffer *t_buf)
{
	ssize_t	i;

	i = 0;
	while (i < t_buf->mem_size)
	{
		if (t_buf->memory[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ut_free_memory(t_buffer *t_buf)
{
	if (t_buf->memory)
	{
		free(t_buf->memory);
		t_buf->memory = NULL;
		t_buf->mem_size = 0;
	}
}
