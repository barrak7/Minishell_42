/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:17:07 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:28 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_split_copy(char **dst, char *src, int *p)
{
	int	i;
	int	len;

	i = 0;
	len = token_split_len(src, *p);
	*dst = malloc(len + 1);
	malloc_err(*dst);
	while (src[*p] && ft_isspace(src[*p]))
		(*p)++;
	if (is_redirection(&src[*p]))
	{
		while (i < len)
			(*dst)[i++] = src[(*p)++];
	}
	if (len == 0 && (src[*p] == '"' || src[*p] == '\''))
		(*p) += 2;
	while (src[*p] && i < len)
	{
		if (src[*p] == '\'' || src[*p] == '"')
			copy_in_quotes((*dst), src, &i, p);
		else
			(*dst)[i++] = src[(*p)++];
	}
	(*dst)[i] = 0;
}

void	redirection_check_help(char *str, t_cmds *cmds, int *s, int *c)
{
	if (!(*s) && !ft_isspace(*str) && !is_redirection(str))
	{
		*s = 1;
		cmds->reds_p[(*c)++] = 0;
	}
}

void	redirections_check(t_cmds *cmds, int count)
{
	int	i;
	int	c;
	int	s;

	i = 0;
	c = 0;
	s = 0;
	cmds->reds_p = malloc(sizeof(int) * count);
	malloc_err(cmds->reds_p);
	while (cmds->args[0][i])
	{
		redirection_check_help(&cmds->args[0][i], cmds, &s, &c);
		i += skip_quotes(&(cmds->args[0][i]));
		if (cmds->args[0][i] && s && ft_isspace(cmds->args[0][i]))
			s = 0;
		else if (cmds->args[0][i] && is_redirection(&cmds->args[0][i]))
		{
			cmds->reds_p[c++] = is_redirection(&cmds->args[0][i]);
			i += cmds->reds_p[c - 1] - 1;
			s = 0;
		}
		if (cmds->args[0][i])
			i++;
	}
}

void	heredoc_check(t_cmds *cmds)
{
	int	i;

	i = 0;
	cmds->doc_expand = 0;
	while (cmds->args[0][i])
	{
		i += skip_quotes(&(cmds->args[0][i]));
		if (cmds->args[0][i] && !ft_strncmp("<<", &(cmds->args[0][i]), 2))
		{
			i += 2;
			while (cmds->args[0][i] && ft_isspace(cmds->args[0][i]))
				i++;
			while (cmds->args[0][i] && !ft_isspace(cmds->args[0][i])
				&& !is_token(&(cmds->args[0][i])))
				i++;
			if (cmds->args[0][i] != '\'' && cmds->args[0][i] != '"')
				cmds->doc_expand = 1;
			else
				cmds->doc_expand = 0;
		}
		if (cmds->args[0][i] && ft_strncmp("<<", &(cmds->args[0][i]), 2)
			&& cmds->args[0][i] != '\'' && cmds->args[0][i] != '"')
			i++;
	}
}

void	token_split(t_cmds *cmds)
{
	int		count;
	char	**new;
	int		i;
	int		p;

	if (!cmds->args)
		return ;
	count = 0;
	token_split_count(cmds->args[0], &count);
	redirections_check(cmds, count);
	heredoc_check(cmds);
	new = malloc(sizeof(char *) * (count + 1));
	malloc_err(new);
	i = 0;
	p = 0;
	while (i < count)
	{
		token_split_copy(&(new[i]), cmds->args[0], &p);
		i++;
	}
	new[i] = 0;
	free(cmds->args[0]);
	free(cmds->args);
	cmds->args = new;
}
