/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbarrak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:10:43 by hbarrak           #+#    #+#             */
/*   Updated: 2023/07/07 15:26:14 by hbarrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_files(t_wildcard *files)
{
	char	*str;
	char	*tmp;

	str = 0;
	tmp = 0;
	while (files)
	{
		if (files->next)
		{
			tmp = ft_strjoin(str, files->file_name);
			free(str);
			str = ft_strjoin(tmp, " ");
			free(tmp);
		}
		else
		{
			tmp = ft_strjoin(str, files->file_name);
			free(str);
			str = tmp;
		}
		files = files->next;
	}
	return (str);
}

char	*expand_wild(char *str)
{
	t_wildcard	*files;
	char		*res;

	files = wild_card(str);
	res = join_files(files);
	delete_list_wildcard(&files);
	free(str);
	return (res);
}

char	*get_expanded(char *str, int start, int end, int is_doc)
{
	int	i;

	i = start;
	while (str[i] && i < end)
	{
		if (str[i] == '"' || str[i] == '\'' || is_doc)
			return (ft_substr(str, start, end - start));
		i++;
	}
	return (expand_wild(ft_substr(str, start, end - start)));
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}
