/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/23 13:18:27 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	if (data->buffer)
		free(data->buffer);
	if (data->first)
		ft_lstfree(data);
	if (data->splitted_args)
		splitted_args_free(data->splitted_args);
	reset(data);
}

static int	mini_routine(t_data *data, char *buffer)
{
	if (buffer[0] == '\0')
		return (1);
	if (split_command(data, buffer))
		return (2);
	if (lexer(data))
		return (3);
	expand(data);
	data->splitted_args = split_arg(data);
	check_exit(data);
	if (execution(data))
		return (4);
	return (0);
}

void	do_sig(int sig)
{
	printf("pid = %d\n", g_pid);
	if (g_pid == 0)
	{
		if (sig == SIGQUIT)
			printf("quit yay!\n");
		if (sig == SIGINT)
			printf("quit C\n");
	}
	else
	{
		if (sig == SIGQUIT)
			printf("no quit\n");
		if (sig == SIGINT)
			printf("quit\n");
	}
	//return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*arg[6];
	char *str;

	init(&data);
	(void)argc;
	(void)argv;
	data.envp = envp;
	data.cd.home = getenv("HOME");
	data.buffer = malloc(1);
	data.buffer[0] = '\0';
	while (data.buffer && data.exit == 0)
	{
		reset_var(&data);
		data.buffer = readline("$> ");
		mini_routine(&data, data.buffer);
		//printf("%d\n", d);
		if (data.buffer)
			add_history(data.buffer);
	}
	return (0);
}
