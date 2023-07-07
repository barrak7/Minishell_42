/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:01:44 by hbouabda          #+#    #+#             */
/*   Updated: 2023/04/04 13:31:55 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_lb;

void	free_cmds_list(void)
{
	t_cmds	*tmp;

	while (g_lb.cmds)
	{
		tmp = g_lb.cmds;
		g_lb.cmds = g_lb.cmds->next;
		free_matrix(tmp->args);
		free(tmp->heredoc);
		free(tmp->reds_p);
		free(tmp->ambi_re);
		if (tmp->out != 0 && tmp->out != 1 && tmp->out != 2)
			close(tmp->out);
		if (tmp->in != 0 && tmp->in != 1 && tmp->in != 2)
			close(tmp->in);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*lst_envp;
	char	*input;

	lst_envp = envp_to_list(envp);
	initial_value(lst_envp);
	setup_term();
	argc = 0;
	argv = 0;
	(signal(SIGINT, sigint_handler), signal(SIGQUIT, SIG_IGN));
	input = readline("minishell> ");
	while (input != NULL)
	{
		if (*input)
		{
			add_history(input);
			huge_parser(input);
			execute_cmds(g_lb.cmds);
			signal(SIGINT, sigint_handler);
			signal(SIGQUIT, SIG_IGN);
			free_cmds_list();
		}
		free(input);
		input = readline("minishell> ");
	}
	return (g_lb.exs);
}
