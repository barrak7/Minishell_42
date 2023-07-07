/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:16:04 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:40 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_err(char *str)
{
	int		c;
	char	*err1;
	char	*err2;
	char	*err3;
	char	*err4;

	c = is_token(str);
	err1 = "minishell: syntax error near unexpected token `<'\n";
	err2 = "minishell: syntax error near unexpected token `>'\n";
	err3 = "minishell: syntax error near unexpected token `<<'\n";
	err4 = "minishell: syntax error near unexpected token `>>'\n";
	str = "minishell: syntax error near unexpected token `|'\n";
	if (c == 1)
		return (set_exit(err1, 258));
	if (c == 2)
		return (set_exit(err2, 258));
	if (c == 3)
		return (set_exit(err3, 258));
	if (c == 4)
		return (set_exit(err4, 258));
	if (c == 5)
		return (set_exit(str, 258));
	return (0);
}

int	check_tokens(char *str)
{
	int	i;
	int	t;
	int	tmp;

	i = 0;
	t = 0;
	while (str[i])
	{
		tmp = skip_quotes(&str[i]);
		i += tmp;
		if (tmp || (str[i] && !ft_isspace(str[i]) && !is_token(&str[i])))
			t = 0;
		else if (!t && is_redirection(&str[i]))
		{
			t = is_redirection(&str[i]);
			i += t - 1;
		}
		else if (t && (is_redirection(&str[i]) || str[i] == '|'))
			return (token_err(&str[i]));
		if (str[i])
			i++;
	}
	if (t)
		return (check_endl(0, 0));
	return (1);
}

int	skip_quotes(char *str)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		q = str[i++];
		while (str[i] && str[i] != q)
			i++;
		if (str[i] == q)
			i++;
	}
	return (i);
}

void	check_heredoc_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str && str[i])
	{
		i += skip_quotes(&str[i]);
		if (!ft_strncmp("<<", &str[i], 2))
		{
			i += 1;
			c += 1;
		}
		if (str[i])
			i++;
	}
	if (c > 16)
	{
		set_exit("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
}

int	is_redirection(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (2);
	if (!ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "<", 1))
		return (1);
	if (!ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}
