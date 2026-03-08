/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: steven <steven@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:57:55 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/22 23:01:42 by steven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -n;
	}
	else
		num = n;
	if (num < 10)
	{
		ft_putchar_fd(num + '0', fd);
		return ;
	}
	ft_putnbr_fd((int)(num / 10), fd);
	ft_putchar_fd((int)((num % 10) + '0'), fd);
}
