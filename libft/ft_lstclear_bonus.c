/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:41:07 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/27 18:42:51 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lsth;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		lsth = *lst;
		(*lst) = (*lst)->next;
		ft_lstdelone(lsth, del);
	}
}
