/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:06:04 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:29:08 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wild_card_help_1(t_wild_norm *w_n, char *str, int i, int wild)
{
	if (str[i + 1] == 0 && wild)
	{
		while (w_n->tmp->file_name[w_n->tmp->pointer]
			&& w_n->tmp->file_name[w_n->tmp->pointer + 1])
			w_n->tmp->pointer++;
		if (w_n->tmp->file_name[w_n->tmp->pointer] != str[i])
			w_n->del = 1;
	}
	else
	{
		if (!w_n->tmp->file_name[w_n->tmp->pointer])
			w_n->del = 1;
		while (w_n->tmp->file_name[w_n->tmp->pointer] && wild)
		{
			if (w_n->tmp->file_name[w_n->tmp->pointer++] == str[i])
				break ;
		}
		if (wild && str[i] != w_n->tmp->file_name[w_n->tmp->pointer - 1])
			w_n->del = 1;
		if (!wild)
			if (w_n->tmp->file_name[w_n->tmp->pointer++] != str[i])
				w_n->del = 1;
	}
}

void	else_cringe_w(t_wildcard **prev, t_wildcard **tmp)
{
	if (*prev != *tmp)
		*prev = (*prev)->next;
	*tmp = (*tmp)->next;
}

void	sort_files(t_wildcard **envp_sorted)
{
	t_wildcard	*prev;
	t_wildcard	*next;
	t_wildcard	*tmp;

	tmp = *envp_sorted;
	prev = *envp_sorted;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->file_name, tmp->next->file_name) > 0)
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
			else_cringe_w(&prev, &tmp);
	}
}

void	wild_card_help_2(t_wild_norm *w_n, char *str, int i, int wild)
{
	t_wildcard	*tmp_2;

	w_n->del = 0;
	wild_card_help_1(w_n, str, i, wild);
	tmp_2 = w_n->tmp;
	w_n->tmp = w_n->tmp->next;
	if (w_n->del)
		delete_node_wildcard(&w_n->files_list, tmp_2);
}

t_wildcard	*wild_card(char *str)
{
	t_wild_norm		w_n;
	int				i;
	int				wild;
	t_wildcard		*files_list;

	files_list = 0;
	i = 0;
	if (includes_v2(str, '*') == -1)
		return (add_back_wildcard(&files_list, wild_new_node(str)), files_list);
	w_n.files_list = create_wildcard_list(str);
	while (str[i])
	{
		w_n.tmp = w_n.files_list;
		wild = 0;
		while (str[i] == '*' && ++i)
			wild = 1;
		while (w_n.tmp && str[i])
			wild_card_help_2(&w_n, str, i, wild);
		if (str[i])
			i++;
	}
	if (!w_n.files_list)
		add_back_wildcard(&w_n.files_list, wild_new_node(str));
	return (sort_files(&w_n.files_list), w_n.files_list);
}
