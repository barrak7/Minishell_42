/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:42:44 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:56 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_export(int fd, int flag)
{
	t_envp	*tmp;
	t_envp	*tt;

	tmp = sort_envp(g_lb.env);
	tt = tmp;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->var_name, fd);
		if (tmp->equal_sign)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->var_content, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		tmp = tmp->next;
	}
	clear_list(&tt);
	g_lb.exs = 0;
	if (flag)
		exit(0);
}

void	export(t_cmds *cmd, int fd, int flag)
{
	char	**vars;
	int		i;
	int		ex;

	ex = 0;
	i = 0;
	vars = cmd->args;
	if (!cmd->args[1])
	{
		norm_export(fd, flag);
		return ;
	}
	while (vars[++i])
	{
		if (export_helper(&g_lb.env, vars[i]))
			ex = 1;
	}
	g_lb.exs = ex;
	if (flag)
		exit(ex);
}

int	export_valid_varname(char *str, int flag)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(str);
	if (!*str)
		return (free(tmp), 0);
	if (tmp[ft_strlen(tmp) - 1] == '+' && flag)
		tmp[ft_strlen(tmp) - 1] = '0';
	if (ft_isdigit(tmp[0]))
	{
		free(tmp);
		return (0);
	}
	while (tmp[++i])
	{
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_')
		{
			free(tmp);
			return (0);
		}
	}
	free(tmp);
	return (1);
}
