/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:42:57 by hbarrak           #+#    #+#             */
/*   Updated: 2023/03/27 15:47:31 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s, char const *s1)
{
	char	*p;
	size_t	al;

	al = ft_strlen(s) + ft_strlen(s1) + 1;
	p = ft_calloc(al, sizeof(char));
	if (p)
	{
		ft_strlcat(p, s, al);
		ft_strlcat(p, s1, al);
	}
	return (p);
}
