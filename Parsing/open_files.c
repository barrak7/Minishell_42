/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:52:09 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:27:01 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_heredocs(void)
{
	t_cmds	*cmds;
	int		c;

	cmds = g_lb.cmds;
	c = fork();
	fd_error(c);
	if (!c)
	{
		signal(SIGINT, SIG_DFL);
		while (cmds)
		{
			if (cmds->args)
			{
				if (cmds->doc_expand)
					expand_doc(cmds);
				else
					read_doc(cmds);
			}
			cmds = cmds->next;
		}
		exit(0);
	}
	else
		check_doc_exit();
}

void	open_in(t_cmds *cmds, char *file, int *br)
{
	if (cmds->in != 0 && cmds->in != 1 && cmds->in != 2)
		close(cmds->in);
	if (!ft_strcmp(file, "/dev/stdin"))
	{
		cmds->in = 0;
		return ;
	}
	else if (!ft_strcmp(file, "/dev/stdout"))
	{
		cmds->in = 1;
		return ;
	}
	else if (!ft_strcmp(file, "/dev/stderr"))
	{
		cmds->in = 2;
		return ;
	}
	cmds->in = open(file, O_RDONLY);
	*br = files_error(cmds->in, file);
}

int	ambi_file(t_cmds *cmds, int *br)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (cmds->args[i])
	{
		if (c == cmds->ambiguious)
		{
			if (cmds->in != 0 && cmds->in != 1 && cmds->in != 2)
				close(cmds->in);
			if (cmds->out != 0 && cmds->out != 1 && cmds->out != 2)
				close(cmds->out);
			*br = 1;
			write(2, "minishell: ", 11);
			write(2, cmds->ambi_re, ft_strlen(cmds->ambi_re));
			write(2, ": ambiguous redirect\n", 21);
			cmds->in = -1;
			g_lb.exs = 1;
			return (1);
		}
		(cmds->reds_p[i]) && c++;
		i++;
	}
	return (0);
}

void	open_files_app(t_cmds *cmds, int *i, int *br)
{
	*br = 0;
	if (ambi_file(cmds, br))
		return ;
	if (!ft_strcmp(">>", cmds->args[*i]))
		open_append(cmds, cmds->args[++(*i)], br);
	else if (!ft_strcmp("<<", cmds->args[*i]))
	{
		if (cmds->in != 0 && cmds->in != 1 && cmds->in != 2)
			close(cmds->in);
		cmds->in = open(cmds->heredoc, O_RDONLY);
		fd_error(cmds->in);
		(*i)++;
	}
	else if (!ft_strcmp(">", cmds->args[*i]))
		open_out(cmds, cmds->args[++(*i)], br);
	else if (!ft_strcmp("<", cmds->args[*i]))
		open_in(cmds, cmds->args[++(*i)], br);
}

void	open_files(void)
{
	t_cmds	*cmds;
	int		i;
	int		br;

	cmds = g_lb.cmds;
	g_lb.signaled = 0;
	create_herdoc(cmds);
	open_heredocs();
	while (cmds)
	{
		i = 0;
		cmds->in = 0;
		cmds->out = 1;
		while (cmds->args && cmds->args[i])
		{
			if (cmds->reds_p[i])
			{
				open_files_app(cmds, &i, &br);
				if (br)
					break ;
			}
			i++;
		}
		cmds = cmds->next;
	}
}
