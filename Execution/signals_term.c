/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:56:17 by hbouabda          #+#    #+#             */
/*   Updated: 2023/07/07 15:28:59 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signum)
{
	signum = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_lb.exs = 1;
	return ;
}

void	sigint_handler_2(int signum)
{
	(void)signum;
	write(1, "^C\n", 3);
}

void	sigint_handler_3(int signum)
{
	(void)signum;
	write(1, "^\\Quit: 3\n", 11);
}

void	setup_term(void)
{
	struct termios	new;

	tcgetattr(0, &new);
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &new);
}

char	*is_var_set(char *var)
{
	t_envp	*tmp;

	tmp = g_lb.env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->var_name, var))
			return (tmp->var_name);
		tmp = tmp->next;
	}
	return (NULL);
}
