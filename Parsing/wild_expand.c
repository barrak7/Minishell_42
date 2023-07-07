/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 20:57:39 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:22 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_wild(char *str, int start, int end)
{
	int		i;
	char	*exp;
	int		len;

	i = start;
	while (str[i] && i < end)
	{
		if (str[i] == '\'' || str[i] == '"')
			return (end - start);
		i++;
	}
	str = ft_substr(str, start, end - start);
	exp = expand_wild(str);
	len = ft_strlen(exp);
	free(exp);
	return (len);
}

int	wildcard_len(char *str)
{
	int	i;
	int	len;
	int	s;

	i = 0;
	len = 0;
	s = 0;
	while (str[i])
	{
		s = skip_spaces(&str[i]);
		len += s;
		i += s;
		s = is_redirection(&str[i]);
		i += s;
		len += s;
		s = i;
		i += skip_quotes(&str[i]);
		while (str[i] && !ft_isspace(str[i]) && !is_redirection(&str[i]))
			i++;
		len += check_wild(str, s, i);
	}
	return (len);
}

int	ft_concat(char *dst, char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
	return (j);
}

void	copy_sp_red(char *new, char *str, int *i, int norm_var[3])
{
	norm_var[2] = 0;
	while (ft_isspace(str[*i]) || is_redirection(&str[*i]))
	{
		if (!ft_strncmp("<<", &str[*i], 2))
			norm_var[2] = 1;
		new[norm_var[1]++] = str[(*i)++];
	}
}

char	*wild_expand(char *str)
{
	int		i;
	char	*new;
	int		norm_var[3];
	char	*tmp;

	i = 0;
	new = malloc(wildcard_len(str) + 1);
	malloc_err(new);
	norm_var[1] = 0;
	norm_var[0] = 0;
	while (str[i])
	{
		copy_sp_red(new, str, &i, norm_var);
		norm_var[0] = i;
		while (str[i] && !ft_isspace(str[i]) && !is_redirection(&str[i]))
			i++;
		tmp = get_expanded(str, norm_var[0], i, norm_var[2]);
		new[norm_var[1]] = 0;
		norm_var[1] += ft_concat(new, tmp);
		free(tmp);
	}
	new[norm_var[1]] = 0;
	return (new);
}
