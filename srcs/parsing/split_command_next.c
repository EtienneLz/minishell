/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:07:24 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:07:24 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_quoted(char *command, int i, char quote)
{
	int	len;
	int	end;

	len = 1;
	end = 0;
	i++;
	while (command[i])
	{
		if (command[i] == quote)
		{
			end = 1;
			break ;
		}
		len++;
		i++;
	}
	if (end == 0)
		return (-1);
	return (len + 1);
}
