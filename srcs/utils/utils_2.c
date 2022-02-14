/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:32:08 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 09:32:08 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(t_token	*actual)
{
	if (actual->next)
		actual = actual->next;
	else
		return (0);
	while (actual && actual->type == STRING || actual->type == STRING_SIMPLE || actual->type == OPTION)
	{
		if (actual->next == NULL)
			return (0);
		if (actual->next->type == PIPE)
			return (1);
		actual = actual->next;
	}
	return (0);
}

t_token	*to_next_command(t_token *actual)
{
	t_token	*act;

	act = actual;
	if (act->next == NULL)
		return (NULL);
	act = act->next;
	while (act && act->type != COMMAND)
	{
		act = act->next;
	}
	return (act);
}

void	check_exit(t_data *data)
{
	t_token	*actual;

	actual = data->first;
	while (actual)
	{
		if (actual->type == COMMAND)
			if (!ft_strcmp(actual->content, "exit"))
				ft_exit(data, 0);
		actual = actual->next;
	}
}