/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:06:06 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:29:03 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_wildcard	*wild_new_node(char *file_name)
{
	t_wildcard	*node;

	node = malloc(sizeof(t_wildcard));
	node->file_name = ft_strdup(file_name);
	node->pointer = 0;
	node->next = 0;
	return (node);
}

void	add_back_wildcard(t_wildcard **head, t_wildcard *new)
{
	t_wildcard	*node;

	if (!head)
		return ;
	node = *head;
	if (!*head)
		*head = new;
	else
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

void	delete_node_wildcard(t_wildcard **head, t_wildcard *to_delete)
{
	t_wildcard	*node;
	t_wildcard	*tmp;

	if (!head || !to_delete)
		return ;
	node = *head;
	if (*head == to_delete)
	{
		*head = (*head)->next;
		free(node->file_name);
		free(node);
		return ;
	}
	while (node)
	{
		if (node->next == to_delete)
		{
			tmp = node->next;
			node->next = node->next->next;
			free(tmp->file_name);
			free(tmp);
			return ;
		}
		node = node->next;
	}
}

void	delete_list_wildcard(t_wildcard **head)
{
	t_wildcard	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->file_name);
		free(tmp);
	}
}

t_wildcard	*create_wildcard_list(char *str)
{
	t_wildcard		*files_list;
	DIR				*dir;
	struct dirent	*ent;

	files_list = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (*str != '.')
		{
			if (*(ent->d_name) != '.')
				add_back_wildcard(&files_list, wild_new_node(ent->d_name));
		}
		else
			add_back_wildcard(&files_list, wild_new_node(ent->d_name));
		ent = readdir(dir);
	}
	closedir(dir);
	return (files_list);
}
