/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:04:47 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:46 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	childs_odd(char **envp, int pipefd[2][2], t_cmds *cmd)
{
	close(pipefd[1][0]);
	close(pipefd[0][1]);
	if (cmd->in < 0 || cmd->out < 0)
		exit(1);
	if (cmd->in == 0)
		dup2(pipefd[0][0], 0);
	else
		dup2(cmd->in, 0);
	if (cmd->out == 1)
		dup2(pipefd[1][1], 1);
	else
		dup2(cmd->out, 1);
	if (is_built_in(cmd) == -1)
		if (execve(check_access(cmd->args[0]), cmd->args, envp) == -1)
			exit_fun(127, cmd->args[0]);
}

void	childs_even(char **envp, int pipefd[2][2], t_cmds *cmd)
{
	close(pipefd[1][1]);
	close(pipefd[0][0]);
	if (cmd->in < 0 || cmd->out < 0)
		exit(1);
	if (cmd->in == 0)
		dup2(pipefd[1][0], 0);
	else
		dup2(cmd->in, 0);
	if (cmd->out == 1)
		dup2(pipefd[0][1], 1);
	else
		dup2(cmd->out, 1);
	if (is_built_in(cmd) == -1)
		if (execve(check_access(cmd->args[0]), cmd->args, envp) == -1)
			exit_fun(127, cmd->args[0]);
}

void	childs_bloc_in_multi(int i, int pipefd[2][2], t_cmds *cmd)
{
	char		**envp;
	static void	(*operations[7])(t_cmds *, int fd, int flag) = {echo, pwd, \
			env, unset, cd, export, ft_exit};

	if (!cmd->args || !cmd->args[0])
		exit(0);
	signal(SIGQUIT, SIG_DFL);
	envp = list_to_env();
	if (i % 2)
	{
		childs_odd(envp, pipefd, cmd);
		operations[is_built_in(cmd)](cmd, 1, 1);
	}
	else
	{
		childs_even(envp, pipefd, cmd);
		operations[is_built_in(cmd)](cmd, 1, 1);
	}
	free_matrix(envp);
}

void	first_child(int *pipefd1, t_cmds *cmd)
{
	char		**envp;
	static void	(*operations[7])(t_cmds *, int fd, int flag) = {echo, pwd, \
			env, unset, cd, export, ft_exit};

	if (!cmd->args || !cmd->args[0])
		exit(0);
	signal(SIGQUIT, SIG_DFL);
	envp = list_to_env();
	close(pipefd1[0]);
	if (cmd->in < 0 || cmd->out < 0)
		exit(1);
	dup2(cmd->in, 0);
	if (cmd->out != 1)
		dup2(cmd->out, 1);
	else
		dup2(pipefd1[1], 1);
	if (is_built_in(cmd) == -1)
		if (execve(check_access(cmd->args[0]), cmd->args, envp) == -1)
			exit_fun(127, cmd->args[0]);
	operations[is_built_in(cmd)](cmd, 1, 1);
}

void	last_child(int *pipefd1, t_cmds *cmd)
{
	char		**envp;
	static void	(*operations[7])(t_cmds *, int fd, int flag) = {echo, pwd, \
			env, unset, cd, export, ft_exit};

	if (!cmd->args || !cmd->args[0])
		exit(0);
	signal(SIGQUIT, SIG_DFL);
	envp = list_to_env();
	while (cmd->next)
		cmd = cmd->next;
	close(pipefd1[1]);
	if (cmd->in < 0 || cmd->out < 0)
		exit(1);
	dup2(cmd->out, 1);
	if (cmd->in != 0)
		dup2(cmd->in, 0);
	else
		dup2(pipefd1[0], 0);
	if (is_built_in(cmd) == -1)
		if (execve(check_access(cmd->args[0]), cmd->args, envp) == -1)
			exit_fun(127, cmd->args[0]);
	operations[is_built_in(cmd)](cmd, 1, 1);
}
