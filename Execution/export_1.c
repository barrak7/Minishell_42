/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:25:12 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:53 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_helper_sub_1(char **tmp_1, char **tmp_2, char *var)
{
	if (*var == '=')
	{
		ft_printf("minishell: export: '", var,
			"': not a valid identifier\n", 2);
		return (1);
	}
	*tmp_1 = ft_substr(var, 0, includes(var, '='));
	*tmp_2 = ft_substr(var, includes(var, '=') + 1, ft_strlen(var));
	if (!export_valid_varname(*tmp_1, 1) || \
		((*tmp_1)[ft_strlen(*tmp_1) - 1] == '+' && includes_v2(var, '=') == -1))
	{
		ft_printf("minishell: export: '", *tmp_1,
			"': not a valid identifier\n", 2);
		return (free(*tmp_1), free(*tmp_2), 1);
	}
	return (0);
}

void	export_helper_sub_2(char *var, t_envp **envp)
{
	if (includes_v2(var, '=') != -1)
		get_last_node(*envp)->equal_sign = 1;
	else
		get_last_node(*envp)->equal_sign = 0;
}

int	export_helper_sub_3(char *var, t_envp **envp, char *tmp_1, t_envp *tmp_lst)
{
	char	*tmp_2;
	char	*tmp_3;

	tmp_2 = ft_substr(var, includes(var, '=') + 1, ft_strlen(var));
	tmp_1[ft_strlen(tmp_1) - 1] = 0;
	while (tmp_lst)
	{
		if (!ft_strcmp(tmp_lst->var_name, tmp_1))
		{
			free(tmp_1);
			tmp_1 = tmp_lst->var_content;
			tmp_lst->var_content = ft_strjoin(tmp_lst->var_content, tmp_2);
			tmp_lst->equal_sign = 1;
			return (free(tmp_1), free(tmp_2), 0);
		}
		tmp_lst = tmp_lst->next;
	}
	tmp_3 = ft_strjoin(tmp_1, "=");
	free(tmp_1);
	tmp_1 = ft_strjoin(tmp_3, tmp_2);
	add_back(envp, new_node(tmp_1));
	export_helper_sub_2(var, envp);
	return (free(tmp_1), free(tmp_2), free(tmp_3), 0);
}

int	export_helper_sub_4(t_envp *tmp_lst, char *tmp_1, char *tmp_2, char *var)
{
	if (!ft_strcmp(tmp_lst->var_name, tmp_1))
	{
		if (*tmp_2)
		{
			free(tmp_lst->var_content);
			tmp_lst->var_content = tmp_2;
		}
		else
			free(tmp_2);
		if (includes_v2(var, '=') != -1)
			tmp_lst->equal_sign = 1;
		return (free(tmp_1), 1);
	}
	return (0);
}

int	export_helper(t_envp **envp, char *var)
{
	char	*tmp_1;
	char	*tmp_2;
	t_envp	*tmp_lst;

	tmp_lst = *envp;
	if (export_helper_sub_1(&tmp_1, &tmp_2, var))
		return (1);
	else if (tmp_1[ft_strlen(tmp_1) - 1] == '+')
		return (free(tmp_2), export_helper_sub_3(var, envp, tmp_1, tmp_lst), 0);
	while (tmp_lst)
	{
		if (export_helper_sub_4(tmp_lst, tmp_1, tmp_2, var))
			return (1);
		tmp_lst = tmp_lst->next;
	}
	add_back(envp, new_node(var));
	export_helper_sub_2(var, envp);
	return (free(tmp_1), free(tmp_2), 0);
}
