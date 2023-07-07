/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:42:19 by hbarrak           #+#    #+#             */
/*   Updated: 2023/04/02 14:27:57 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	spl(char c, char const *s, int *i)
{
	int	len;

	len = 0;
	while (c == s[*i] && s[*i])
		(*i)++;
	while (c != s[len + *i] && s[len + *i])
		len++;
	return (len);
}

static void	fr_s(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

int	wc(char const *s, char c)
{
	int	w;
	int	i;
	int	ac;

	w = 1;
	ac = 0;
	i = 0;
	while (s[i])
	{
		if (c != s[i] && s[i])
		{
			if (w == 1)
			{
				ac++;
				w = 0;
			}
		}
		else
			w = 1;
		i++;
	}
	return (ac);
}

char	**ft_split(char const *s, char c)
{
	int		ac;
	int		i;
	char	**p;
	int		len;
	int		j;

	if (!s)
		return (0);
	ac = wc(s, c);
	i = 0;
	j = 0;
	p = ft_calloc((ac + 1), sizeof(char *));
	while (p && j < ac)
	{
		len = spl(c, s, &i);
		p[j] = ft_substr(s, i, len);
		if (!p[j])
		{
			fr_s(p);
			return (0);
		}
		i += len;
		j++;
	}
	return (p);
}
