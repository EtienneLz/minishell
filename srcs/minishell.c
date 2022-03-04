/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:23:09 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:23:09 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	if (data->buffer)
		free(data->buffer);
	minifree(data);
	reset(data);
}

static int	mini_routine(t_data *data, char *buffer)
{
	if (!buffer)
	{
		reset_var(data);
		ft_exit(data, NULL);
	}
	if (buffer[0] == '\0')
		return (1);
	if (split_command(data, buffer))
		return (2);
	remove_quotes(data);
	if (lexer(data))
		return (0);
	if (last_check(data) == 2)
		return (0);
	if (data->heredoc > 0)
		get_sep(data);
	expand(data);
	data->splitted_args = split_arg(data);
	structure(data);
	check_exit(data);
	data->pid = mallocer(data->pid, sizeof(int) * data->nb_command);
	execution(data);
	return (0);
}

void	prompt(t_data *data)
{
	reset_var(data);
	data->buffer = line_prompt("\e[1m\e[34mminishell> \e[0m");
	mini_routine(data, data->buffer);
	if (data->buffer)
		add_history(data->buffer);
}

char	*line_prompt(char *prompt)
{
	char	*buffer;

	buffer = "";
	buffer = readline(prompt);
	return (buffer);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init(&data);
	(void)argc;
	(void)argv;
	if (envp)
	{
		data.envp = envp;
		data.cd.home = getenv("HOME");
	}
	else
	{
		ft_putstr_fd("minishell> ", 2);
		ft_putstr_fd("Fatal error: environment variables not set", 2);
	}
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	data.buffer = malloc(1);
	data.buffer[0] = '\0';
	while (data.buffer)
		prompt(&data);
	return (0);
}
