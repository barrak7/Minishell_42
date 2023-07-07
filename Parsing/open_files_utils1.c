/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:09:01 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:27:06 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_doc(t_cmds *cmds)
{
	int		i;
	int		fd;
	char	*buffer;

	i = 0;
	while (cmds->args[i])
	{
		if (!ft_strcmp("<<", cmds->args[i]) && cmds->reds_p[i])
		{
			fd = open(cmds->heredoc, O_WRONLY | O_TRUNC);
			fd_error(fd);
			buffer = readline("> ");
			i++;
			while (buffer)
				buffer = read_doc_app(buffer, cmds->args[i], fd);
			close(fd);
		}
		i++;
	}
}

char	*expand_doc_app(char *buffer, char *limiter, int fd)
{
	char	*exp_buffer;

	if (!ft_strcmp(limiter, buffer))
	{
		free(buffer);
		return (NULL);
	}
	exp_buffer = heredoc_expand(buffer);
	free(buffer);
	write(fd, exp_buffer, ft_strlen(exp_buffer));
	write(fd, "\n", 1);
	free(exp_buffer);
	buffer = readline("> ");
	return (buffer);
}

void	expand_doc(t_cmds *cmds)
{
	int		i;
	int		fd;
	char	*buffer;

	i = 0;
	while (cmds->args[i])
	{
		if (cmds->reds_p[i] && !ft_strcmp("<<", cmds->args[i]))
		{
			fd = open(cmds->heredoc, O_WRONLY | O_TRUNC);
			fd_error(fd);
			buffer = readline("> ");
			i++;
			while (buffer)
				buffer = expand_doc_app(buffer, cmds->args[i], fd);
			close(fd);
		}
		i++;
	}
}

void	heredoc_handler(int a)
{
	a = 1;
	write(1, "\n", 1);
	return ;
}
