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

void	prompt(t_data *data)
{
	while (data.buffer)
	{
		//signal(SIGQUIT, do_sig);
		//signal(SIGINT, do_sig);
		reset_var(&data);
		data.buffer = readline("$> ");
		mini_routine(&data, data.buffer);
		if (data.buffer)
			add_history(data.buffer);
	}
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
	char	*arg[2];
	char	*unset[7];

	init(&data);
	(void)argc;
	(void)argv;
	data.envp = envp;
	data.cd.home = getenv("HOME");
	unset[0] = "unset";
	unset[1] = "OLDPWD=bibi";
	unset[2] = "hello";
	unset[3] = "5884";
	unset[4] = "_36684";
	unset[5] = "blop=bof";
	unset[6] = NULL;
	//main_unset(&data, unset);
	//export_no_arg(&data);
	//main_export(&data, unset);
	//printf("mawie = %s\n", getenv("mawie"));
	//printf("zsh = %s\n", getenv("ZSH"));
	arg[0] = "cd";
	//arg[1] = "..";
	//arg[2] = "blop";
	arg[1] = NULL;
	//ft_pwd(&data);
	//main_cd(&data, arg);
	//ft_pwd(&data);
	main_export(&data, unset);
	main_export(&data, arg);
	/*data.buffer = malloc(1);
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
	}*/
	return (0);
}
