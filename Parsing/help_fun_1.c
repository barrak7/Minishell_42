/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:39:48 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:27:55 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**envp_out;

	i = 0;
	while (envp[i])
		if (envp[i][0])
			i++;
	envp_out = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		if (envp[i][0])
		{
			envp_out[i] = ft_strdup(envp[i]);
			i++;
		}
	}
	envp_out[i] = 0;
	return (envp_out);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

char	**ft_join_elem_to_matrix(char **matrix, char *elem)
{
	char	**matrix_out;
	int		i;

	i = 0;
	while (matrix[i])
		i++;
	matrix_out = malloc(sizeof(char *) * i + 2);
	i = -1;
	while (matrix[++i])
		matrix_out[i] = matrix[i];
	matrix_out[i++] = elem;
	matrix_out[i] = 0;
	free(matrix);
	return (matrix_out);
}

char	**list_to_env(void)
{
	char	**env_out;
	char	*tmp_1;
	t_envp	*tmp_env;
	int		i;

	i = 0;
	tmp_env = g_lb.env;
	env_out = malloc(sizeof(char *) * (get_list_len(g_lb.env) + 1));
	while (tmp_env)
	{
		tmp_1 = ft_strjoin(tmp_env->var_name, "=");
		env_out[i++] = ft_strjoin(tmp_1, tmp_env->var_content);
		free(tmp_1);
		tmp_env = tmp_env->next;
	}
	env_out[i] = 0;
	return (env_out);
}

void	ft_printf(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}
