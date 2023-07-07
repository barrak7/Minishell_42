/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:35:16 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:27:59 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_err(void *ptr)
{
	if (!ptr)
	{
		perror("minishell");
		exit(1);
	}
}

void	check_doc_exit(void)
{
	int	status;
	int	exs;

	signal(SIGINT, heredoc_handler);
	wait(&status);
	signal(SIGINT, sigint_handler);
	if (WIFEXITED(status))
	{
		exs = WEXITSTATUS(status);
		if (exs == 1)
			exit(1);
	}
	else if (WIFSIGNALED(status))
	{
		g_lb.signaled = 1;
		g_lb.exs = 1;
	}
}

void	fd_error(int fd)
{
	if (fd < 0)
	{
		perror("minishell");
		exit(1);
	}
}

int	files_error(int fd, char *file)
{
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		if (!*file)
			write(2, ": ", 2);
		perror(file);
		g_lb.exs = 1;
		return (1);
	}
	return (0);
}

int	ambiguity_re(char *str)
{
	if (!*str)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
