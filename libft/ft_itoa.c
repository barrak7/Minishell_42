/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:56:19 by hbarrak           #+#    #+#             */
/*   Updated: 2022/10/27 18:34:01 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_al(int c, int n, long *t, int *i)
{
	char	*p;
	long	tmp;

	tmp = n;
	if (n < 0)
	{
		p = malloc((c + 2) * sizeof(char));
		*i = c + 1;
		*t = tmp * -1;
	}
	else
	{
		p = malloc((c + 1) * sizeof(char));
		*i = c;
		*t = n;
	}
	return (p);
}

static char	*ft_o(void)
{
	char	*p;

	p = ft_calloc(2, sizeof(char));
	if (p)
		p[0] = '0';
	return (p);
}

static int	ft_dc(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		c;
	char	*p;
	int		i;
	long	t;

	if (n == 0)
		return (ft_o());
	c = ft_dc(n);
	p = ft_al(c, n, &t, &i);
	if (p)
	{
		p[i] = '\0';
		i--;
		while (t)
		{
			p[i] = (t % 10) + 48;
			t /= 10;
			i--;
		}
		if (n < 0)
			p[i] = '-';
	}
	return (p);
}
