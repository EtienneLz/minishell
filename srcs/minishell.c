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
	minifree(data);
	reset(data);
}

static int	mini_routine(t_data *data, char *buffer)
{
	if (!buffer)
	{
		reset_var(data);
		ft_exit(data, NULL);
		//exit(0);
	}
	if (buffer[0] == '\0')
		return (1);
	if (split_command(data, buffer))
		return (2);
	if (lexer(data))
		return (3);
	//if (data->heredoc > 0)
	//	ft_heredoc(data);
	expand(data);
	data->splitted_args = split_arg(data);
	structure(data);
	check_exit(data);
	data->pid = malloc(sizeof(int) * data->nb_command);
	if (execution(data))
		return (4);
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

	buffer = malloc(1);
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
	data.envp = envp;
	data.cd.home = getenv("HOME");
	/*unset[0] = "unset";
	unset[1] = "OLDPWD=bibi";
	unset[2] = "hello";
	unset[3] = "5884";
	unset[4] = "_36684";
	unset[5] = "blop=bof";
	unset[6] = NULL;
	main_unset(&data, unset);
	export_no_arg(&data);
	main_export(&data, unset);
	printf("mawie = %s\n", getenv("mawie"));
	printf("zsh = %s\n", getenv("ZSH"));
	arg[0] = "cd";
	arg[1] = "..";
	arg[2] = "blop";
	arg[1] = NULL;
	ft_pwd(&data);
	/main_cd(&data, arg);
	ft_pwd(&data);
	main_export(&data, unset);
	main_export(&data, arg);*/
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	data.buffer = malloc(1);
	data.buffer[0] = '\0';
	while (data.buffer)
	{
		reset_var(&data);
		data.buffer = line_prompt("\e[1m\e[34mminishell> \e[0m");
		mini_routine(&data, data.buffer);
		//printf("%d\n", d);
		if (data.buffer)
			add_history(data.buffer);
	}
	return (0);
}
