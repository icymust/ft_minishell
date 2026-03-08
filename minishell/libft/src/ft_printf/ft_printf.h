/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:41:29 by smorlier          #+#    #+#             */
/*   Updated: 2025/11/26 12:02:56 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		ut_putstr(char *str);
int		ut_putchar(char c);
int		putb(ssize_t n, char *base);
int		ut_pt_ptr(void *ptr, char *base);
size_t	ut_strlen(const char *s);
#endif
