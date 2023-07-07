/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:52:47 by hbarrak           #+#    #+#             */
/*   Updated: 2022/11/14 21:09:50 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dc(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	po(int c)
{
	int	i;

	i = 1;
	c -= 1;
	while (c)
	{
		i *= 10;
		c--;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int			c;
	int			p;
	long int	t;

	t = n;
	if (t < 0)
	{
		t *= -1;
		ft_putchar_fd('-', fd);
	}
	if (t == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	c = dc(t);
	p = po(c);
	while (p)
	{
		ft_putchar_fd((t / p) + 48, fd);
		t %= p;
		p /= 10;
	}
}
