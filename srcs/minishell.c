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
	init(data);
}

static int	mini_routine(t_data *data, char *buffer)
{
	if (buffer[0] == '\0')
		return (1);
	if (split_command(data, buffer))
		return (0);
	if (tokenizer(data))
		return (0);
	if (execution(data))
		return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	//char	*arg[3];

	init(&data);
	/*arg[0] = "export";
	arg[1] = "ZSH=hello";
	arg[2] = NULL;*/
	//main_check(&data, arg);
	//export_args(&data, arg);
	//export_no_arg(&data);
	(void)argc;
	(void)argv;
	(void)envp;
	data.buffer = malloc(1);
	while (data.buffer)
	{
		reset_var(&data);
		data.buffer = readline("$> ");
		mini_routine(&data, data.buffer);
	}
	return (0);
}
