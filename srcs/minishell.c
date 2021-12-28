/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2021/12/28 16:26:48 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*buffer;
	getenv("PATH");

	
	buffer = "";
	while (buffer)
	{
		buffer = readline("$> ");
		printf("cmd = %s\n", buffer);
	}
	free(buffer);
	write(STDOUT, "So you have chosen death\n", 26);
	return (0);
}
