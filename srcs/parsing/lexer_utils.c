/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:13:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 21:13:12 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lexer_2(t_token *actual)
{
	if (actual->type == PIPE && actual->next->type == 0)
		actual->next->type = COMMAND;
	else
		actual->next->type = STRING;
	actual = actual->next;
	return (actual);
}

t_token	*lasts_commands_2(t_token *actual, int *check)
{
	actual->type = is_redirection(actual->content);
	if (actual->next && actual->next->next
		&& actual->next->next->type == STRING)
	{
		actual->next->next->type = COMMAND;
		(*check) = 1;
	}
	else if (actual->next && actual->next->next)
		actual = actual->next->next;
	else
		actual = NULL;
	return (actual);
}

void	final_lex(t_data *data)
{
	t_token	*actual;

	actual = data->first;
	while (actual)
	{
		if (is_redirection(actual->content))
			actual->type = is_redirection(actual->content);
		actual = actual->next;
	}
	create_files(data);
	counter(data);
}
