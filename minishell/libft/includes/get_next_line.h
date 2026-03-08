/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:25:19 by smorlier          #+#    #+#             */
/*   Updated: 2025/08/07 15:34:21 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char		buffer[BUFFER_SIZE];
	char		*memory;
	ssize_t		mem_size;
}	t_buffer;

char	*get_next_line(int fd);
void	*ut_memmove(void *dst, const void *src, ssize_t len);
void	*ut_memcpy(void *dst, const void *src, ssize_t n);
int		ut_nl_in(t_buffer *t_buf);
void	ut_clean_buffer(char *buffer, ssize_t size);
void	ut_free_memory(t_buffer *t_buf);
#endif
