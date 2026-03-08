/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:42:23 by smorlier          #+#    #+#             */
/*   Updated: 2025/08/07 15:33:49 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	initialisation(t_buffer *t_buf, int fd)
{
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (0);
	if (read(fd, t_buf->buffer, 0) < 0)
	{
		ut_free_memory(t_buf);
		return (0);
	}
	if (t_buf->memory == NULL)
	{
		t_buf->memory = malloc(1);
		if (t_buf->memory == NULL)
			return (0);
		t_buf->mem_size = 0;
	}
	return (1);
}

char	*ut_catch_line(t_buffer *t_buf)
{
	char	*str;
	ssize_t	len;
	int		nl_pos;

	if (t_buf->mem_size == 0)
		return (NULL);
	nl_pos = ut_nl_in(t_buf);
	if (nl_pos == -1)
		len = t_buf->mem_size;
	else
		len = nl_pos + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ut_memmove(str, t_buf->memory, len);
	str[len] = '\0';
	if (len < t_buf->mem_size)
	{
		ut_memmove(t_buf->memory, &t_buf->memory[len], t_buf->mem_size - len);
		t_buf->mem_size -= len;
	}
	else
		t_buf->mem_size = 0;
	return (str);
}

static int	aggregate_memory(t_buffer *t_buf, size_t read_nb)
{
	char	*new_memory;
	ssize_t	new_size;

	if (read_nb == 0)
		return (0);
	new_size = t_buf->mem_size + read_nb;
	if (new_size < t_buf->mem_size)
		return (-1);
	new_memory = malloc(new_size);
	if (new_memory == NULL)
		return (-1);
	ut_memmove(new_memory, t_buf->memory, t_buf->mem_size);
	ut_memmove(&new_memory[t_buf->mem_size], t_buf->buffer, read_nb);
	free(t_buf->memory);
	t_buf->memory = new_memory;
	t_buf->mem_size = new_size;
	return (1);
}

static int	update_memory(t_buffer *t_buf, int fd)
{
	ssize_t	read_nb;

	while (ut_nl_in(t_buf) == -1)
	{
		ut_clean_buffer(t_buf->buffer, BUFFER_SIZE);
		read_nb = read(fd, t_buf->buffer, BUFFER_SIZE);
		if (read_nb < 0)
		{
			ut_free_memory(t_buf);
			return (read_nb);
		}
		if (read_nb == 0)
			return (t_buf->mem_size);
		if (aggregate_memory(t_buf, read_nb) < 0)
		{
			ut_free_memory(t_buf);
			return (-1);
		}
	}
	return (t_buf->mem_size);
}

char	*get_next_line(int fd)
{
	static t_buffer	t_buf;
	int				update_status;
	char			*line;

	if (!initialisation(&t_buf, fd))
		return (NULL);
	if (t_buf.mem_size == 0 || ut_nl_in(&t_buf) == -1)
	{
		update_status = update_memory(&t_buf, fd);
		if (update_status < 0)
			return (NULL);
		if (update_status == 0 && t_buf.mem_size == 0)
		{
			if (t_buf.memory)
				ut_free_memory(&t_buf);
			return (NULL);
		}
	}
	line = ut_catch_line(&t_buf);
	if (!line && t_buf.memory != NULL)
		ut_free_memory(&t_buf);
	return (line);
}
