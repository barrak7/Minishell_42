/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:35:26 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/28 10:56:20 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*d;

	if (!b)
		return (0);
	d = (unsigned char *)b;
	len -= 1;
	while (len + 1)
	{
		d[len] = (unsigned char)c;
		len--;
	}
	return (b);
}
