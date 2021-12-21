/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2021/12/21 18:56:18 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(char **envp)
{
	char	*buffer;
	size_t	buffer_size;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	buffer_size = 2048;
	if (!buffer)
		return (1);
	write (STDOUT, "$> ", 3);
	while (getline(&buffer, &buffer_size, stdin) > 0)
	{
		printf("cmd = %s", buffer);
		write (STDOUT, "$> ", 3);
	}
	free(buffer);
	write(STDOUT, "So you have chosen death\n", 26);
	return (0);
}
