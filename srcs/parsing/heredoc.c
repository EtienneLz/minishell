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

static void	here_read(t_data *data, char **sep, int fd, char *file)
{
	char	*ret;
	int		code;
	char	*buffer;

	code = 0;
	buffer = NULL;
	while (1)
	{
		buffer = readline("> ");
		if (here_break(data, buffer, &code, sep))
			break ;
		if (!ft_strcmp(buffer, sep[data->heredoc_nb]))
			break ;
		if (!ft_strcmp(buffer, ""))
		{
			ft_putstr_fd("\n", fd);
			continue ;
		}
		ret = here_expand(data, buffer);
		ft_putstr_fd(ret, fd);
		ft_putstr_fd("\n", fd);
		free(ret);
	}
	here_free(data, file, sep);
	exit(code);
}

static int	process(t_data *data, char **sep, int fd, char *file)
{
	int		status;
	int		ret;
	pid_t	pid;

	status = 0;
	ret = 0;
	pid = fork();
	g_pid = pid;
	if (pid == 0)
	{
		signal(SIGINT, signal_heredoc);
		here_read(data, sep, fd, file);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		ret = WIFEXITED(status);
		if (ret > 0)
			ret = WEXITSTATUS(status);
		signal(SIGQUIT, signal_handler);
	}
	data->ret = ret;
	g_pid = 0;
	return (ret);
}

static int	ft_heredoc(t_data *data, char **sep)
{
	int		fd;
	char	*file;
	t_token	*actual;
	int		ret;

	ret = 0;
	actual = data->first;
	while (sep[data->heredoc_nb])
	{
		while (actual && actual->next && actual->type != LL_ARROW)
			actual = actual->next;
		actual = actual->next;
		file = concanate(data->heredoc_nb, "tmp/.");
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		ret = process(data, sep, fd, file);
		close(fd);
		free(actual->content);
		actual->content = ft_strdup(file);
		free(file);
		if (ret > 0)
			return (ret);
		data->heredoc_nb++;
	}
	return (ret);
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
	free(sep);
	return (ret);
}
