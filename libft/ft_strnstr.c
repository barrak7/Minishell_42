/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:35:26 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 11:05:46 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *tf, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l;

	if (!s || !tf)
		return (0);
	if ((!len && !tf[0]) || (!s[0] && !tf[0]))
		return ((char *)s);
	l = ft_strlen(s);
	i = 0;
	while (i != len && i != l)
	{
		j = 0;
		while (s[i + j] == tf[j] && (i + j) < len && (s[i + j] || tf[j]))
			j++;
		if (!tf[j])
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
