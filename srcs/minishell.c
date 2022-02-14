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
	//expand(data);
	check_exit(data);
	if (execution(data))
		return (4);
	return (0);
}

void	do_sig(int sig)
{
	//printf("pid = %d\n", g_pid);
	//signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (g_pid != 0)
	{
		//if (!(kill(g_pid, sig)))
		//{
		if (sig == SIGQUIT)
			printf("quit \\\n");
		if (sig == SIGINT)
			printf("quit C\n");
		//}
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		//signal(SIGQUIT, SIG_IGN);
		//printf("pid = %d\n", g_pid);
		if (sig == SIGQUIT)
		{
			printf("do nothing");
			//return ;
		}
		if (sig == SIGINT)
			printf("$>");
	}
	//signal(SIGQUIT, do_sig);
	//signal(SIGINT, do_sig);
	//return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*arg[6];
	char *str;

	init(&data);
	/*data.envp = envp;
	arg[0] = "unset";
	arg[1] = "ZSH=hello";
	arg[2] = "56labla";
	arg[3] = "papi=poop";
	arg[4] = "lk:po=54";
	arg[5] = NULL;
	main_export(&data, arg);
	export_no_arg(&data);*/
	(void)argc;
	(void)argv;
	data.envp = envp;
	data.cd.home = getenv("HOME");
	data.buffer = malloc(1);
	//signal(SIGQUIT, do_sig);
	//signal(SIGINT, do_sig);
	data.buffer[0] = '\0';
	while (data.buffer)
	{
		//signal(SIGQUIT, do_sig);
		//signal(SIGINT, do_sig);
		reset_var(&data);
		data.buffer = readline("$> ");
		mini_routine(&data, data.buffer);
		//printf("%d\n", d);
		if (data.buffer)
			add_history(data.buffer);
	}
	return (0);
}
