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

static char	*here_expand(t_data *data, char *buffer)
{
	char	**split_str;
	char	*ret;
	char	*replaced;
	int		i;

	i = 0;
	split_str = ft_split_noskip(buffer, '$');
	while (split_str[i])
	{
		if (split_str[i][0] == '$')
		{
			if (split_str[i][1] == '?' && split_str[i][2] == '\0')
				replaced = ft_itoa(data->ret);
			else
				replaced = size_var(data, split_str[i]);
			free(split_str[i]);
			split_str[i] = replaced;
		}
		i++;
	}
	ret = unsplit(split_str);
	if (split_str)
		free_tab(split_str);
	return (ret);
}

/*static void	heredoc_sig(int sig)
{
	if (sig == SIGINT)
		g_pid = 1;
	//signal(SIGINT, SIG_IGN);
	signal_handler(sig);
}*/

static void	here_read(t_data *data, char *buffer, char *sep, int fd)
{
	char	*ret;

	while (1)
	{
		signal(SIGINT, signal_heredoc);
		buffer = readline("> ");
		if (!buffer)
		{
			printf("minishell: warning: heredoc delimited by EOF ");
			printf("(wanted `%s\')\n", sep);
			break ;
		}
		if (!ft_strcmp(buffer, sep))
			break ;
		if (!ft_strcmp(buffer, ""))
		{
			ft_putstr_fd("\n", fd);
			continue ;
		}
		ret = here_expand(data, buffer);
		free(buffer);
		ft_putstr_fd(ret, fd);
		ft_putstr_fd("\n", fd);
		free(ret);
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

static int	ft_heredoc(t_data *data, char **sep)
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
		here_read(data, buffer, sep[data->heredoc_nb], fd);
		if (g_pid == -1000)
			return (1);
		close(fd);
		actual->content = ft_strdup(file);
		free(file);
		data->heredoc_nb++;
	}
	return (0);
}

int	get_sep(t_data *data)
{
	char	**sep;
	t_token	*actual;
	int		i;
	int		ret;

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
	ret = ft_heredoc(data, sep);
	if (ret)
		data->ret = 128;
	free_tab(sep);
	return (ret);
}
