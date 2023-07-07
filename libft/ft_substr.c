/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:17:21 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/19 20:42:08 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		p = ft_calloc(1, sizeof(char));
		return (p);
	}
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start + 1;
		p = malloc(len * sizeof(char));
	}
	else
	{
		len += 1;
		p = malloc(len * sizeof(char));
	}
	if (p)
		ft_strlcpy(p, &s[start], len);
	return (p);
}
