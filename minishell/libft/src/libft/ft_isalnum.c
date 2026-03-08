/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:56:33 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/18 14:42:12 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	isalpha;
	int	isnum;

	isalpha = 0;
	isnum = 0;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		isalpha = 1;
	if (c >= '0' && c <= '9')
		isnum = 1;
	return (isnum || isalpha);
}
