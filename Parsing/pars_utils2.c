/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:42:22 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:50 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char *str)
{
	if (!ft_strncmp(str, "'", 1))
		return (1);
	if (!ft_strncmp(str, "\"", 1))
		return (2);
	if (!ft_strncmp(str, "<<", 2))
		return (3);
	if (!ft_strncmp(str, ">>", 2))
		return (4);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (2);
	if (!ft_strncmp(str, "|", 1))
		return (5);
	return (0);
}

int	ft_copy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (src && src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len);
}

int	is_expandable(char c, int i)
{
	static int	doll;

	if (!doll && c == '$' && !i)
	{
		doll = 1;
		return (1);
	}
	if (doll)
	{
		doll = 0;
		return (0);
	}
	if (c == '?' && !i)
		return (1);
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	expand_app(char *new, char *str, int i, int len)
{
	int	q;

	q = 0;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		if (!q && !ft_strncmp("<<", &str[i], 2))
		{
			len += ft_copy(&new[len], &str[i], skip_limiter(&str[i])) - 1;
			i += skip_limiter(&str[i]) - 1;
		}
		else if ((!q || q == '"') && str[i] == '$')
			len += cp_env(&new[len], &str[i + 1], &i, q) - 1;
		else
			new[len] = str[i];
		i++;
		len++;
	}
	new[len] = 0;
}

char	*expand(char *str)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = expand_len(str);
	new = malloc(len + 1);
	malloc_err(new);
	len = 0;
	expand_app(new, str, i, len);
	return (new);
}
