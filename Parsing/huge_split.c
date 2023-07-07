/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huge_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:43:21 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:27:16 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmds	*new_cmds_node(void)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	malloc_err(cmds);
	cmds->args = 0;
	cmds->doc_expand = 0;
	cmds->heredoc = 0;
	cmds->in = 0;
	cmds->out = 1;
	cmds->reds_p = 0;
	cmds->next = 0;
	cmds->ambiguious = -1;
	cmds->ambi_re = 0;
	return (cmds);
}

int	quotes_len(char *str, int *len)
{
	int	i;
	int	q;

	i = 0;
	if (str[i] != '\'' && str[i] != '"')
		return (0);
	q = str[i];
	i++;
	while (str[i] && str[i] != q)
		i++;
	if (str[i] && str[i] == q)
		i++;
	(*len) += i;
	return (i);
}

int	split_len(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q && q == str[i])
			q = 0;
		if (!q && str[i] == '|')
			break ;
		i++;
	}
	return (i);
}

void	split_copy(t_cmds *dst, char *src, int len)
{
	int	i;

	i = 0;
	dst->args = malloc(sizeof(char *));
	malloc_err(dst->args);
	dst->args[0] = malloc(len + 1);
	malloc_err(dst->args[0]);
	ft_copy(dst->args[0], src, len);
}

void	huge_split(char *str)
{
	int		i;
	t_cmds	*cmds;
	int		len;

	i = 0;
	g_lb.cmds = new_cmds_node();
	cmds = g_lb.cmds;
	cmds->args = 0;
	while (str[i])
	{
		len = split_len(&str[i]);
		split_copy(cmds, &str[i], len);
		i += len;
		if (str[i] == '|')
		{
			cmds->next = new_cmds_node();
			cmds = cmds->next;
			i++;
		}
	}
	cmds->next = 0;
}
