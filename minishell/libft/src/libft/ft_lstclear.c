/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:08:17 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/24 11:08:18 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*nptr;

	if (lst == NULL || del == NULL)
		return ;
	ptr = *lst;
	nptr = ptr;
	while (ptr != NULL)
	{
		nptr = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = nptr;
	}
	*lst = NULL;
}
