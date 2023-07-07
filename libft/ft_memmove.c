/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:45:30 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 10:55:50 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	if ((!src && !dst) || (dst == src))
		return (0);
	s = (char *)src;
	d = (char *)dst;
	if (src < dst)
	{
		len -= 1;
		while (len + 1)
		{
			d[len] = s[len];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
