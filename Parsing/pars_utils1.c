/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:38:06 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:54 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *str, char c, int q)
{
	int		i;
	t_envp	*env;

	env = g_lb.env;
	i = 0;
	if (str[i] == '?')
		return (ft_itoa(g_lb.exs));
	else if (str[i] == '$')
		return ("$$");
	else if (!str[i] && (c == '"' || c == '\'') && !q)
		return (NULL);
	else if (ft_isspace(str[i]) || !str[i] || (!str[i] && q))
		return ("$");
	while (env)
	{
		if (!ft_strcmp(env->var_name, str))
			return (env->var_content);
		env = env->next;
	}
	return (NULL);
}

int	env_len(char *str, int *l, int *s, int q)
{
	int		i;
	int		len;
	char	*tmp;
	char	*env;

	i = 0;
	while (str[i] && is_expandable(str[i], i))
		i++;
	tmp = malloc(i + 1);
	malloc_err(tmp);
	i = 0;
	while (str[i] && is_expandable(str[i], i))
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = 0;
	env = get_env(tmp, str[i], q);
	len = ft_strlen(env);
	if (tmp[0] == '?')
		free(env);
	*s = ft_strlen(tmp) + 1;
	*l += (*s) - 1;
	free(tmp);
	return (len);
}

int	skip_limiter(char *str)
{
	int	i;
	int	q;

	i = 2;
	q = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (!q && (is_token(&str[i]) || ft_isspace(str[i])))
			break ;
		i++;
	}
	return (i);
}

int	expand_len(char *str)
{
	int	i;
	int	q;
	int	s;
	int	len;

	i = 0;
	q = 0;
	s = 0;
	len = 0;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (!q && !ft_strncmp("<<", &str[i], 2))
			i += skip_limiter(&str[i]) - 1;
		else if (str[i] == '$' && (!q || q == '"'))
			len += env_len(&str[i + 1], &i, &s, q);
		i++;
	}
	len += i - s;
	return (len);
}

int	cp_env(char *dest, char *src, int *l, int q)
{
	int		i;
	int		len;
	char	*tmp;
	char	*env;

	i = 0;
	len = 0;
	while (src[len] && is_expandable(src[len], len))
		len++;
	*l += len;
	tmp = malloc(len + 1);
	malloc_err(tmp);
	while (src[i] && i < len)
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = 0;
	env = get_env(tmp, src[i], q);
	len = ft_copy(dest, env, ft_strlen(env));
	if (tmp[0] == '?')
		free(env);
	free(tmp);
	return (len);
}
