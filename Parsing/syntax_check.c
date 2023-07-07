/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:48:26 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:36 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_exit(char *err, int exs)
{
	write(2, err, ft_strlen(err));
	g_lb.exs = exs;
	return (0);
}

int	check_quotes(char *str)
{
	int		i;
	int		q;
	char	*tmp;

	i = 0;
	q = 0;
	tmp = "minishell: syntax error near unexpected token `newline'\n";
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		i++;
	}
	if (q)
		return (set_exit(tmp, 258));
	return (1);
}

int	check_endl(int i, char *str)
{
	char	*tmp;
	int		j;

	j = 0;
	while (str && ft_isspace(str[j]))
		j++;
	if (str && !str[j])
		return (1);
	tmp = "minishell: syntax error near unexpected token `newline'\n";
	if (!i)
	{
		write(2, tmp, 56);
		g_lb.exs = 258;
		return (0);
	}
	return (1);
}

int	check_pipes(char *str)
{
	int		i;
	int		s;
	char	*tmp;

	i = 0;
	s = 0;
	tmp = "minishell: syntax error near unexpected token `|'\n";
	while (str[i])
	{
		if (str[i] != '|' && !ft_isspace(str[i]))
			s = 1;
		i += skip_quotes(&str[i]);
		if (str[i] == '|' && !s)
			return (set_exit(tmp, 258));
		if (str[i] == '|' && s)
			s = 0;
		if (str[i])
			i++;
	}
	return (check_endl(s, str));
}

int	syntax_check(char *str)
{
	if (!check_tokens(str))
		return (0);
	if (!check_pipes(str))
		return (0);
	if (!check_quotes(str))
		return (0);
	check_heredoc_count(str);
	return (1);
}
