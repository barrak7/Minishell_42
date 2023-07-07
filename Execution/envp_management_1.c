/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_management_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:19:23 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:31 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp	*new_node(char *var_line)
{
	t_envp	*lst;

	lst = malloc(sizeof(t_envp));
	lst->var_name = ft_substr(var_line, 0, includes(var_line, '='));
	lst->var_content = ft_substr(var_line, includes(var_line, '=') + 1,
			ft_strlen(var_line));
	lst->next = NULL;
	return (lst);
}

t_envp	*get_last_node(t_envp *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_back(t_envp **head, t_envp *new)
{
	if (!head)
		return ;
	if (head && *head)
	{
		get_last_node(*head)->next = new;
		return ;
	}
	*head = new;
}

t_envp	*envp_to_list(char **envp)
{
	int		i;
	t_envp	*list;

	i = 0;
	list = 0;
	while (envp[i])
	{
		add_back(&list, new_node(envp[i++]));
		get_last_node(list)->equal_sign = 1;
	}
	return (list);
}

int	get_list_len(t_envp *list_envp)
{
	int	i;

	i = 0;
	while (list_envp)
	{
		list_envp = list_envp->next;
		i++;
	}
	return (i);
}
