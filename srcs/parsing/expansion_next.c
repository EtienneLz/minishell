/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_next.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:05:27 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:05:27 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand(t_data *data)
{
	t_token	*actual;

	actual = data->first;
	while (actual)
	{
		if (actual->content && (actual->type == STRING || actual->type == COMMAND))
		{
			if (actual->content[0] == '\"')
				actual->content = check_quotes(data, actual->content);
			check_var(data, actual->content, actual);
		}
		else if (actual->type == STRING_SIMPLE)
			if (actual->content[0] == '\'')
				actual->content = check_quotes(data, actual->content);
		actual = actual->next;
	}
}
