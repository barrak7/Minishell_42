/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huge_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:54:49 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:27:19 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_with_quotes(char *dst, char *src, int *p, int *p1)
{
	int	q;

	if (src[*p1] != '\'' && src[*p1] != '"')
		return ;
	q = src[*p1];
	dst[(*p)++] = src[(*p1)++];
	while (src[*p1] && src[*p1] != q)
	{
		dst[(*p)++] = src[(*p1)++];
	}
	if (src[*p1])
		dst[(*p)++] = src[(*p1)++];
}

int	ambi_exp_check(char *str)
{
	char	*tmp;
	int		i;
	int		s;

	tmp = expand(str);
	str = wild_expand(tmp);
	free(tmp);
	i = 0;
	while (str[i])
	{
		i += skip_quotes(&str[i]);
		s = i;
		while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
		tmp = ft_substr(str, s, i - s);
		if (wc(tmp, ' ') > 1 || wc(tmp, '\t') > 1)
		{
			free(tmp);
			free(str);
			return (1);
		}
		free(tmp);
	}
	return (ambiguity_re(str));
}

int	ambiguity_expand(char *str, t_cmds *cmd)
{
	int		i;
	int		s;
	char	*tmp;
	int		re;

	i = 0;
	i += is_redirection(str);
	i += skip_spaces(&str[i]);
	s = i;
	while (str[i] && !is_redirection(&str[i]) && !ft_isspace(str[i]))
		i++;
	tmp = ft_substr(str, s, i - s);
	re = ambi_exp_check(tmp);
	cmd->ambi_re = tmp;
	return (re);
}

int	check_ambiguity(char *str, t_cmds *cmd)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		i += skip_spaces(&str[i]);
		i += skip_quotes(&str[i]);
		if (str[i] && is_redirection(&str[i]) && ft_strncmp("<<", &str[i], 2))
		{
			if (!ambiguity_expand(&str[i], cmd))
				c++;
			else
				return (c);
		}
		else if (str[i] && !ft_strncmp("<<", &str[i], 2))
		{
			c++;
			i++;
		}
		if (str[i])
			i++;
	}
	return (-1);
}

int	huge_parser(char *str)
{
	t_cmds	*cmds;
	char	*tmp;

	if (!str || !str[0] || !syntax_check(str))
		return (0);
	huge_split(str);
	cmds = g_lb.cmds;
	while (cmds)
	{
		if (cmds->args)
		{
			cmds->ambiguious = check_ambiguity(cmds->args[0], cmds);
			tmp = expand(cmds->args[0]);
			free(cmds->args[0]);
			cmds->args[0] = wild_expand(tmp);
			free(tmp);
		}
		token_split(cmds);
		cmds = cmds->next;
	}
	open_files();
	remove_files();
	return (0);
}
