/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:49:52 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 11:01:30 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	l;
	char	*p;

	if (!s1)
		return (0);
	i = 0;
	l = ft_strlen(s1);
	p = ft_calloc(l + 1, sizeof(char));
	if (p)
	{
		while (s1[i])
		{
			p[i] = s1[i];
			i++;
		}
	}
	return (p);
}
