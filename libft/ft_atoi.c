/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 11:22:37 by hbarrak           #+#    #+#             */
/*   Updated: 2023/03/10 11:17:54 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dc(const char *s, int j)
{
	int	i;

	i = 0;
	while (s[j] && s[j] == '0')
		j++;
	while (s[j] && ft_isdigit(s[j]))
	{
		j++;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	re;
	int					sign;
	int					j;

	i = 0;
	re = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	j = i;
	while (ft_isdigit(str[i]))
		re = re * 10 + (str[i++] - 48);
	if (sign == 1 && (re > 9223372036854775807 || (ft_dc(str, j) > 19)))
		return (-1);
	else if (sign == -1 && (re > 9223372036854775807 || (ft_dc(str, j) > 19)))
		return (0);
	return (re * sign);
}
