/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorlier <smorlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:47:34 by smorlier          #+#    #+#             */
/*   Updated: 2025/07/28 09:57:56 by smorlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	clean_on_fail(t_list *p, t_list *lst, void *c, void (*del)(void *))
{
	if (p == NULL)
	{
		del(c);
		ft_lstclear(&lst, del);
		return (1);
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*p;
	t_list	*previous;
	void	*cont;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	newlst = NULL;
	previous = NULL;
	while (lst)
	{
		cont = f(lst->content);
		p = ft_lstnew(cont);
		if (clean_on_fail(p, newlst, cont, del))
			return (NULL);
		if (previous != NULL)
			previous->next = p;
		if (newlst == NULL)
			newlst = p;
		previous = p;
		lst = lst->next;
	}
	return (newlst);
}
