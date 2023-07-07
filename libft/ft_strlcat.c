/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:05:47 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 11:04:10 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	sl;
	size_t	dl;
	size_t	s;

	if (!src || (!dst && dstsize))
		return (0);
	sl = ft_strlen(src);
	if (!dst && !dstsize)
		return (sl);
	dl = ft_strlen(dst);
	s = dstsize - dl;
	if (dstsize == 0 || dstsize <= dl)
		return (sl + dstsize);
	ft_strlcpy(&dst[dl], src, s);
	return (sl + dl);
}
