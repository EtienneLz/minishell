/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 12:36:39 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	ft_lstfree(data);
	splitted_args_free(data->splitted_args);
}

static void	mini_routine(t_data *data, char *buffer)
{
	if (split_command(data, buffer))
		return ;
	if (tokenizer(data))
		return ;
	if (execution(data))
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	init(&data);
	while (data.buffer)
	{
		data.buffer = readline("$> ");
		mini_routine(&data, data.buffer);
		reset_var(&data);
	}
	return (0);
}
