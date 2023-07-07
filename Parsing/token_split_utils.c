/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:18:08 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:31 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_split_count(char *str, int *c)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (str[i])
	{
		if (!s && !ft_isspace(str[i]) && !is_redirection(&str[i]))
		{
			s = 1;
			(*c)++;
		}
		i += skip_quotes(&str[i]);
		if (str[i] && is_redirection(&str[i]))
		{
			s = 0;
			(*c)++;
			i += is_redirection(&str[i]) - 1;
		}
		else if (ft_isspace(str[i]))
			s = 0;
		if (str[i])
			i++;
	}
}

int	token_split_len(char *str, int start)
{
	int	q;
	int	len;

	q = 0;
	len = 0;
	while (ft_isspace(str[start]))
		start++;
	if (is_redirection(&str[start]))
		return (is_redirection(&str[start]));
	while (str[start])
	{
		if (!q && (str[start] == '"' || str[start] == '\''))
			q = str[start];
		else if (q && str[start] == q)
			q = 0;
		if ((!q && !ft_isspace(str[start]) && !is_redirection(&str[start])
				&& str[start] != '"' && str[start] != '\'') || (q
				&& str[start] != q))
			len++;
		if (!q && ((ft_isspace(str[start])) || is_redirection(&str[start])))
			break ;
		start++;
	}
	return (len);
}

void	copy_in_quotes(char *dst, char *src, int *p, int *p1)
{
	int	q;

	q = src[*p1];
	(*p1)++;
	while (src[*p1] && src[*p1] != q)
	{
		dst[*p] = src[*p1];
		(*p1)++;
		(*p)++;
	}
	if (src[*p1])
		(*p1)++;
}
