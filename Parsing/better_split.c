/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:41:10 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:07 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	spl(char c, char const *s, int *i)
{
	int	len;

	len = 0;
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

// static int	wc(char const *s, char c)
// {
// 	int	i;
// 	int	ac;

// 	ac = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			ac++;
// 		i++;
// 	}
// 	return (++ac);
// }

char	**better_split(char const *s, char c)
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
		i += len + 1;
		j++;
	}
	return (p);
}

char	*ft_lower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
	return (str);
}
