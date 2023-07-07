/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:16:39 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 10:54:25 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*p1;

	if (s1 == s2)
		return (0);
	p = (unsigned char *)s1;
	p1 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] != p1[i])
			return (p[i] - p1[i]);
		i++;
	}
	return (0);
}
