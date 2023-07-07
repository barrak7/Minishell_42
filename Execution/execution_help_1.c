/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_help_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:52:10 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:40 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_path(char *path)
{
	while (*path)
	{
		if (*path == '/')
			return (1);
		path++;
	}
	return (0);
}

char	**susano(char **p)
{
	int	i;

	i = 0;
	if (!p[i])
	{
		free(p);
		p = malloc(sizeof(char *) * 2);
		p[0] = ft_strdup(".");
		p[1] = 0;
		return (p);
	}
	while (p[i])
	{
		if (!p[i][0])
		{
			free(p[i]);
			p[i] = ft_strdup(".");
		}
		i++;
	}
	return (p);
}

char	*check_access(char *cmd)
{
	char	**splited_path;
	int		i;
	char	*s;

	if (is_path(cmd))
		return (cmd);
	splited_path = susano(better_split(ft_getenv("PATH"), ':'));
	i = -1;
	while (splited_path[++i])
	{
		s = splited_path[i];
		splited_path[i] = ft_strjoin(s, "/");
		free(s);
		s = ft_strjoin(splited_path[i], cmd);
		if (!access(s, X_OK))
			return (free_matrix(splited_path), s);
		free(s);
	}
	if (*ft_getenv("PATH"))
		ft_printf("minishell: ", cmd, ": command not found\n", 2);
	else
		ft_printf("minishell: ", cmd, ": No such file or directory\n", 2);
	exit(127);
	return (free_matrix(splited_path), NULL);
}
