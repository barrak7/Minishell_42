/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:14:02 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:58 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_append(t_cmds *cmds, char *file, int *br)
{
	if (cmds->out != 0 && cmds->out != 1 && cmds->out != 2)
		close(cmds->out);
	if (!ft_strcmp(file, "/dev/stdin"))
	{
		cmds->out = 0;
		return ;
	}
	else if (!ft_strcmp(file, "/dev/stdout"))
	{
		cmds->out = 1;
		return ;
	}
	else if (!ft_strcmp(file, "/dev/stderr"))
	{
		cmds->out = 2;
		return ;
	}
	cmds->out = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	*br = files_error(cmds->out, file);
}

void	open_out(t_cmds *cmds, char *file, int *br)
{
	if (cmds->out != 0 && cmds->out != 1 && cmds->out != 2)
		close(cmds->out);
	if (!ft_strcmp(file, "/dev/stdin"))
	{
		cmds->out = 0;
		return ;
	}
	else if (!ft_strcmp(file, "/dev/stdout"))
	{
		cmds->out = 1;
		return ;
	}
	else if (!ft_strcmp(file, "/dev/stderr"))
	{
		cmds->out = 2;
		return ;
	}
	cmds->out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*br = files_error(cmds->out, file);
}
