/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_fun_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:54:39 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:25 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env(t_cmds *cmd, int fd, int flag)
{
	int		i;
	t_envp	*list_envp;

	(void)cmd;
	i = 0;
	list_envp = g_lb.env;
	while (list_envp)
	{
		if (list_envp->var_content[0])
		{
			ft_putstr_fd(list_envp->var_name, fd);
			ft_putchar_fd('=', fd);
			ft_putendl_fd(list_envp->var_content, fd);
		}
		list_envp = list_envp->next;
	}
	g_lb.exs = 0;
	if (flag)
		exit(0);
}

void	ft_exit(t_cmds *cmd, int fd, int flag)
{
	(void)fd;
	printf("exit\n");
	if (!cmd->args[1])
		exit(g_lb.exs);
	if (!ft_check_val(cmd->args[1]))
	{
		ft_printf("minishell: exit: ", cmd->args[1], \
			": numeric argument required\n", 2);
		exit(255);
	}
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_lb.exs = 1;
		if (flag)
			exit(1);
		return ;
	}
	if (ft_check_val(cmd->args[1]))
	{
		exit((unsigned char)ft_atoi(cmd->args[1]));
	}
}

void	cd_help_1(char *tmp_1, int flag)
{
	char	cwd[1024];

	if (*ft_getenv("HOME"))
	{
		if (chdir(ft_getenv("HOME")))
		{
			perror("minishell: cd:");
			(free(tmp_1), g_lb.exs = 1);
			if (flag)
				exit(1);
			return ;
		}
		if (is_var_set("OLDPWD"))
			export_helper(&g_lb.env, tmp_1);
		free(tmp_1);
		tmp_1 = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
		if (is_var_set("PWD"))
			export_helper(&g_lb.env, tmp_1);
		free(tmp_1);
		g_lb.exs = 0;
		return ;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	free(tmp_1);
	g_lb.exs = 1;
}

void	cd_help_2(char *tmp_1, int flag)
{
	char	cwd[1024];

	if (is_var_set("OLDPWD"))
		export_helper(&g_lb.env, tmp_1);
	free(tmp_1);
	tmp_1 = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	if (is_var_set("PWD"))
		export_helper(&g_lb.env, tmp_1);
	free(tmp_1);
	g_lb.exs = 0;
	if (flag)
		exit(g_lb.exs);
}

void	cd(t_cmds *cmd, int fd, int flag)
{
	char	cwd[1024];
	char	*tmp_1;

	(void)fd;
	tmp_1 = ft_strjoin("OLDPWD=", getcwd(cwd, sizeof(cwd)));
	if (!cmd->args[1])
	{
		cd_help_1(tmp_1, flag);
		if (flag)
			exit(g_lb.exs);
		return ;
	}
	if (chdir(cmd->args[1]))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(cmd->args[1]);
		free(tmp_1);
		g_lb.exs = 1;
		if (flag)
			exit(g_lb.exs);
		return ;
	}
	cd_help_2(tmp_1, flag);
}
