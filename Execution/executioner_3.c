/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:33:23 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:50 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fail(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	g_lb.exs = 1;
	return (1);
}

void	execute_cmds_help_1(int *fk, t_cmds *cmds, char **envp, int *status)
{
	*fk = fork();
	if (*fk < 0 && fail("fork"))
		exit(g_lb.exs);
	if (!*fk)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmds->in < 0 || cmds->out < 0)
			exit(1);
		dup2(cmds->in, 0);
		dup2(cmds->out, 1);
		if (execve(check_access(cmds->args[0]), cmds->args, envp) == -1)
			exit_fun(127, cmds->args[0]);
	}
	signal(SIGQUIT, sigint_handler_3);
	signal(SIGINT, sigint_handler_2);
	waitpid(*fk, status, 0);
	if (WIFEXITED(*status))
		g_lb.exs = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == 3)
			g_lb.exs = 131;
		else
			g_lb.exs = 130;
	}
}

void	execute_cmds_help_2(int *fk, t_cmds *cmds, int pipefd[2][2])
{
	if (pipe(pipefd[0]) == -1 && fail("pipe"))
		exit(g_lb.exs);
	*fk = fork();
	if (*fk < 0 && fail("fork"))
		exit(g_lb.exs);
	if (!*fk)
		first_child(pipefd[0], cmds);
	else
	{
		multi_pipe(cmds, pipefd);
		*fk = fork();
		if (*fk < 0 && fail("fork"))
			exit(g_lb.exs);
		if (*fk)
			parent_bloc(pipefd, *fk);
		else
			last_child(pipefd[0], cmds);
	}
}

void	execute_cmds(t_cmds *cmds)
{
	int			pipefd[2][2];
	int			fk;
	char		**envp;
	int			status;
	static void	(*operations[7])(t_cmds*, int fd, int flag) = {echo, pwd, env, \
			unset, cd, export, ft_exit};

	if (!cmds || (!cmds->next && \
		(!cmds->args || !cmds->args[0])) || g_lb.signaled)
		return ;
	if (!cmds->next && cmds->args && cmds->args[0])
	{
		envp = list_to_env();
		if (is_built_in(cmds) == -1)
			execute_cmds_help_1(&fk, cmds, envp, &status);
		else
		{
			if (cmds->in < 0 || cmds->out < 0)
				return ;
			operations[is_built_in(cmds)](cmds, cmds->out, 0);
		}
		free_matrix(envp);
		return ;
	}
	execute_cmds_help_2(&fk, cmds, pipefd);
}
