/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:20:03 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/27 18:49:46 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lsth;

	if (!lst || !f || !del)
		return (0);
	new_lst = malloc(sizeof(t_list));
	if (!new_lst)
		return (0);
	lsth = new_lst;
	while (lst->next)
	{
		new_lst->content = f(lst->content);
		new_lst->next = malloc(sizeof(t_list));
		if (!new_lst->next)
		{
			ft_lstclear(&lsth, del);
			return (0);
		}
		new_lst = new_lst->next;
		lst = lst->next;
	}
	new_lst->content = f(lst->content);
	new_lst->next = 0;
	return (lsth);
}
