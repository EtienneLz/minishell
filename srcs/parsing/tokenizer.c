/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:27:37 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/05 18:45:58 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	is_redirection(char *str)
{
	if (!ft_strcmp(str, "|"))
			return (PIPE);
		else if (!ft_strcmp(str, "<"))
			return (L_ARROW);
		else if (!ft_strcmp(str, ">"))
			return (R_ARROW);
		else if (!ft_strcmp(str, "<<"))
			return (LL_ARROW);
		else if (!ft_strcmp(str, ">>"))
			return (RR_ARROW);
	return (0);
}

static void	checker(t_data *data)
{
	t_token	*actual;
	t_token	*next;

	actual = data->first;
	next = actual->next;
	while (actual)
	{
		if (actual->content == COMMAND && next->type == STRING)
			if (next->content[0] == '-')
				next->type == OPTION;
		//else if (actual->type != STRING && actual->type == next->type)
			
		actual = actual->next;
	}
}

void	tokenizer(t_data *data)
{
	t_token	*actual;
	char	type;

	actual = data->first;
	actual->type = COMMAND;
	while (actual->next)
	{
		actual = actual->next;
		type = is_redirection(actual->content);
		if (type)
		{
			actual->type = type;
			if (actual->next)
			{
				if (actual->type == PIPE && is_redirection(actual->next->content) == 0)
					actual->next->type = COMMAND;
				if (actual->type != PIPE && is_redirection(actual->next->content) == 0)
					actual->next->type = FILE;
				actual = actual->next;
			}
		}
		else
			actual->type = STRING;
	}
}