/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_management_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:02:44 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:34 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_3_p(t_envp *p1, char *p2, char *p3)
{
	free(p3);
	free(p2);
	free(p1);
}

void	delete_node(t_envp **list_envp, char *var_name)
{
	t_envp	*tmp;
	t_envp	*tmp_free;

	if (!list_envp || !*list_envp)
		return ;
	if (!ft_strcmp((*list_envp)->var_name, var_name))
	{
		tmp = (*list_envp)->next;
		free_3_p(*list_envp, (*list_envp)->var_name, (*list_envp)->var_content);
		*list_envp = tmp;
		return ;
	}
	tmp = (*list_envp);
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->var_name, var_name))
		{
			tmp_free = tmp->next;
			tmp->next = tmp->next->next;
			free_3_p(tmp_free, tmp_free->var_content, tmp_free->var_name);
			return ;
		}
		tmp = tmp->next;
	}
}

void	else_cringe(t_envp **prev, t_envp **tmp)
{
	if (*prev != *tmp)
		*prev = (*prev)->next;
	*tmp = (*tmp)->next;
}

void	help_sort(t_envp **envp_sorted)
{
	t_envp	*prev;
	t_envp	*next;
	t_envp	*tmp;

	tmp = *envp_sorted;
	prev = *envp_sorted;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->var_name, tmp->next->var_name) > 0)
		{
			next = tmp->next;
			tmp->next = tmp->next->next;
			next->next = tmp;
			if (prev != tmp)
				prev->next = next;
			if (tmp == *envp_sorted)
				*envp_sorted = next;
			tmp = *envp_sorted;
			prev = *envp_sorted;
		}
		else
			else_cringe(&prev, &tmp);
	}
}

t_envp	*sort_envp(t_envp *list_envp)
{
	t_envp	*envp_sorted;
	char	*tmp_;
	char	*tmp_1;
	int		i;

	envp_sorted = 0;
	i = 0;
	while (list_envp)
	{
		tmp_ = ft_strjoin(list_envp->var_name, "=");
		tmp_1 = ft_strjoin(tmp_, list_envp->var_content);
		add_back(&envp_sorted, new_node(tmp_1));
		get_last_node(envp_sorted)->equal_sign = list_envp->equal_sign;
		free(tmp_);
		free(tmp_1);
		list_envp = list_envp->next;
	}
	help_sort(&envp_sorted);
	return (envp_sorted);
}
