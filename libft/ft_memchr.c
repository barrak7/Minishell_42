/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 09:05:57 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 10:54:02 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	if (!s)
		return (0);
	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		if (p[i] == ((unsigned char)c))
			return (&p[i]);
		i++;
	}
	return (0);
}
