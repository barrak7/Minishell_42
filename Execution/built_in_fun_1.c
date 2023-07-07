/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_fun_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:01:56 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:21 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_cmds *cmd, int fd, int flag)
{
	char	cwd[1024];
	t_cmds	*tmp;

	tmp = cmd;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, fd);
		g_lb.exs = 0;
		if (flag)
			exit(0);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		perror("pwd");
		g_lb.exs = 1;
		if (flag)
			exit(1);
	}
}

void	echo(t_cmds *cmd, int fd, int flag)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd->args[++i])
	{
		if (!valid_flag_n(cmd->args[i]))
			break ;
		else
			n = 1;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i++], fd);
		if (cmd->args[i])
			ft_putchar_fd(' ', fd);
	}
	if (!n)
		ft_putchar_fd('\n', fd);
	g_lb.exs = 0;
	if (flag)
		exit(0);
}

void	unset(t_cmds *cmd, int fd, int flag)
{
	int	i;

	i = 1;
	(void)fd;
	g_lb.exs = 0;
	while (cmd->args[i])
	{
		if (!export_valid_varname(cmd->args[i], 0))
		{
			ft_printf("minishell: unset: '", cmd->args[i],
				"': not a valid identifier\n", 2);
			g_lb.exs = 1;
		}
		delete_node(&(g_lb.env), cmd->args[i++]);
	}
	if (flag)
		exit(g_lb.exs);
}
