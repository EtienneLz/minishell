/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 03:07:36 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	ft_lstfree(data);
}

static void	mini_routine(t_data *data, char *buffer)
{
	if (split_command(data, buffer))
		return ;
	if (tokenizer(data))
		return ;
	reset_var(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buffer;

	(void)argc;
	(void)argv;
	(void)envp;
	init(&data);
	while (buffer)
	{
		buffer = readline("$> ");
		mini_routine(&data, buffer);
	}
	//free(buffer);
	return (0);
}
