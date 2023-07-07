/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 10:59:18 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:27:11 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_expand_len(char *str)
{
	int	i;
	int	q;
	int	s;
	int	len;

	i = 0;
	q = 0;
	s = 0;
	len = 0;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '"'))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (str[i] == '$' && str[i + 1] != '\'' && str[i + 1] != '"')
			len += env_len(&str[i + 1], &i, &s, 0);
		i++;
	}
	len += i - s;
	return (len - 1);
}

char	*heredoc_expand(char *str)
{
	int		i;
	int		q;
	int		len;
	char	*new;

	i = 0;
	q = 0;
	len = heredoc_expand_len(str);
	new = malloc(len + 2);
	malloc_err(new);
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\'' && str[i + 1] != '"')
			len += cp_env(&new[len], &str[i + 1], &i, 0) - 1;
		else
			new[len] = str[i];
		i++;
		len++;
	}
	new[len] = 0;
	return (new);
}

char	*get_herdoc_name(int j)
{
	int		i;
	char	*str;
	char	*j_str;
	char	*ttyn;
	int		len;

	ttyn = ttyname(0);
	i = 0;
	j_str = ft_itoa(j);
	len = ft_strlen("/tmp/heredoc") + ft_strlen(j_str) + ft_strlen(&ttyn[5])
		+ 1;
	str = malloc(len + 1);
	malloc_err(str);
	i += ft_copy(str, "/tmp/heredoc", 12);
	i += ft_copy(&str[i], j_str, ft_strlen(j_str));
	str[i++] = '_';
	ft_copy(&str[i], &ttyn[5], ft_strlen(ttyn));
	free(j_str);
	return (str);
}

void	create_herdoc(t_cmds *cmds)
{
	int	i;
	int	j;
	int	fd;

	j = 0;
	while (cmds)
	{
		i = 0;
		cmds->heredoc = 0;
		while (cmds->args && cmds->args[i])
		{
			if (!ft_strcmp("<<", cmds->args[i]) && cmds->reds_p[i])
			{
				cmds->heredoc = get_herdoc_name(j);
				fd = open(cmds->heredoc, O_CREAT | O_TRUNC, 0644);
				fd_error(fd);
				close(fd);
				break ;
			}
			i++;
		}
		j++;
		cmds = cmds->next;
	}
}

char	*read_doc_app(char *buffer, char *limiter, int fd)
{
	if (!ft_strcmp(limiter, buffer))
	{
		free(buffer);
		return (NULL);
	}
	write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
	free(buffer);
	buffer = readline("> ");
	return (buffer);
}
