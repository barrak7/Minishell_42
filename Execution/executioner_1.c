/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:29:16 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:43 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_fun(int status, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (!*cmd)
		ft_putstr_fd(": command not found\n", 2);
	else
		perror(cmd);
	exit(status);
}

int	is_built_in(t_cmds *cmd)
{
	int			i;
	static char	*my_table[8] = {"echo", "pwd", "env", "unset", \
					"cd", "export", "exit", 0};

	i = 0;
	while (my_table[i])
	{
		if (!ft_strcmp(my_table[i], ft_lower(cmd->args[0])))
			return (i);
		i++;
	}
	return (-1);
}

void	parent_bloc(int pipefd[2][2], int fk2)
{
	int	status;

	signal(SIGINT, sigint_handler_2);
	signal(SIGQUIT, sigint_handler_3);
	close(pipefd[0][1]);
	close(pipefd[0][0]);
	waitpid(fk2, &status, 0);
	while (wait(0) > 0)
		;
	if (WIFEXITED(status))
		g_lb.exs = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			g_lb.exs = 131;
		else
			g_lb.exs = 130;
	}
	close(pipefd[1][1]);
	close(pipefd[1][0]);
}

void	parent_bloc_in_multi(int *i, int *pipefd2, int *pipefd1)
{
	if (*i % 2)
	{
		close(pipefd1[0]);
		close(pipefd1[1]);
		if (pipe(pipefd1) == -1 && fail("pipe"))
			exit(g_lb.exs);
	}
	else
	{
		close(pipefd2[0]);
		close(pipefd2[1]);
		if (pipe(pipefd2) == -1 && fail("pipe"))
			exit(g_lb.exs);
	}
	(*i)++;
}

void	multi_pipe(t_cmds *cmd, int pipefd[2][2])
{
	int	i;
	int	fk;

	i = 1;
	cmd = cmd->next;
	if (pipe(pipefd[1]) == -1 && fail("pipe"))
		return ;
	while (cmd && cmd->next)
	{
		fk = fork();
		if (fk < 0)
			exit_fun(5, cmd->args[0]);
		if (!fk)
			childs_bloc_in_multi(i, pipefd, cmd);
		else
			parent_bloc_in_multi(&i, pipefd[1], pipefd[0]);
		cmd = cmd->next;
	}
	if (i % 2 == 0)
	{
		close(pipefd[0][1]);
		close(pipefd[0][0]);
		pipefd[0][0] = pipefd[1][0];
		pipefd[0][1] = pipefd[1][1];
	}
}
