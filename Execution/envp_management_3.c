/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_management_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:46:07 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:37 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_list(t_envp **list_envp)
{
	while (list_envp && (*list_envp))
		delete_node(list_envp, (*list_envp)->var_name);
}

char	*ft_getenv(char *var_name)
{
	t_envp	*tmp;

	tmp = g_lb.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, var_name))
		{
			return (tmp->var_content);
		}
		tmp = tmp->next;
	}
	return ("");
}

void	initial_value(t_envp *envp)
{
	char	*tmp_1;
	char	cwd[1024];

	g_lb.env = envp;
	g_lb.exs = 0;
	export_helper(&g_lb.env, "OLDPWD");
	tmp_1 = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	export_helper(&g_lb.env, tmp_1);
	free(tmp_1);
	if (getenv("SHLVL"))
	{
		tmp_1 = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
		free(tmp_1);
	}
	else
		export_helper(&g_lb.env, "SHLVL=1");
}
