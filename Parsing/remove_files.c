/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:02:18 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:45 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	files_count(int *count, t_cmds *cmds)
{
	int	i;

	*count = 0;
	i = 0;
	while (cmds->args && cmds->args[i])
	{
		if (!cmds->reds_p[i])
			(*count)++;
		i++;
	}
}

void	remove_files_app(t_cmds *cmds, char **dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds->args[i])
	{
		while (cmds->args[i] && cmds->reds_p[i])
			i += 2;
		while (cmds->args[i] && !cmds->reds_p[i])
			dst[j++] = cmds->args[i++];
	}
	dst[j] = 0;
}

void	rm_free(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->args[i])
	{
		if (cmds->reds_p[i])
		{
			free(cmds->args[i]);
			free(cmds->args[++i]);
		}
		i++;
	}
	free(cmds->args);
}

void	remove_files(void)
{
	t_cmds	*cmds;
	int		i;
	char	**new;

	cmds = g_lb.cmds;
	while (cmds)
	{
		if (cmds->args && cmds->ambiguious == -1)
		{
			files_count(&i, cmds);
			new = malloc(sizeof(char *) * (i + 1));
			malloc_err(new);
			remove_files_app(cmds, new);
			rm_free(cmds);
			cmds->args = new;
		}
		cmds = cmds->next;
	}
}
