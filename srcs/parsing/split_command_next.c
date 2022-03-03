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

	len = 1;
	i++;
	while (command[i])
	{
		if (command[i] == quote && (command[i + 1] == ' '
				|| command[i + 1] == '|' || command[i + 1] == '<'
				|| command[i + 1] == '>'))
			break ;
		len++;
		i++;
	}
	return (len + 1);
}
