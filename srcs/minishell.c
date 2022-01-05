/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/05 16:33:14 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	ft_lstfree(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buffer;

	buffer = "";
	(void)argc;
	(void)argv;
	(void)envp;
	init(&data);
	while (buffer)
	{
		buffer = readline("$> ");
		split_command(&data, buffer);
		reset_var(&data);
	}
	//free(buffer);
	write(STDOUT, "So you have chosen death\n", 25);
	return (0);
}
