/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:01:24 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/25 20:46:57 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	here_read(char *buffer, char *sep, int fd)
{
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			printf("minishell: warning: heredoc delimited by EOF ");
			printf("(wanted `%s\')\n", sep);
			break ;
		}
		if (!ft_strcmp(buffer, sep))
			break ;
		ft_putstr_fd(buffer, fd);
		ft_putstr_fd("\n", fd);
		free(buffer);
	}
}

char	*concanate(int j, char *src)
{
	char	*num;
	int		len;
	char	*dest;
	int		i;

	num = ft_itoa(j);
	i = 0;
	len = ft_strlen(num);
	dest = mallocer(&dest, sizeof(char) * (ft_strlen(src) + len + 1));
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	len = 0;
	while (num[len])
	{
		dest[i] = num[len];
		len++;
		i++;
	}
	dest[i] = '\0';
	free(num);
	return (dest);
}

static void	ft_heredoc(t_data *data, char **sep)
{
	int		fd;
	char	*buffer;
	char	*file;
	t_token	*actual;

	actual = data->first;
	buffer = NULL;
	while (sep[data->heredoc_nb])
	{
		while (actual && actual->next && actual->type != LL_ARROW)
			actual = actual->next;
		actual = actual->next;
		file = concanate(data->heredoc_nb, "tmp/.");
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		here_read(buffer, sep[data->heredoc_nb], fd);
		close(fd);
		actual->content = ft_strdup(file);
		free(file);
		data->heredoc_nb++;
	}
}

void	get_sep(t_data *data)
{
	char	**sep;
	t_token	*actual;
	int		i;

	actual = data->first;
	sep = mallocer(&sep, sizeof(char *) * (data->heredoc + 1));
	i = 0;
	while (actual)
	{
		if (actual->type == LL_ARROW)
		{
			sep[i] = actual->next->content;
			i++;
		}
		actual = actual->next;
	}
	sep[i] = NULL;
	ft_heredoc(data, sep);
	free_tab(sep);
	free(sep);
}
