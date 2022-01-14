/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:27:37 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/14 17:12:02 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	is_redirection(t_data *data, char *str)
{
	if (!ft_strcmp(str, "|"))
	{
		data->nb_pipe++;
		return (PIPE);
	}
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

static int	checker(t_data *data)
{
	t_token	*actual;
	t_token	*next;

	actual = data->first;
	next = actual->next;
	while (actual && actual->next)
	{
		if (actual->type == COMMAND && next->type == STRING)
			if (next->content[0] == '-')
				next->type = OPTION;
		if ((actual->type != STRING || actual->type != STRING_SIMPLE)&& actual->type == next->type)
		{
			printf("dddddd\n");
			return (1);
		}
		actual = next;
		next = actual->next;
	}
	return (0);
}

int	tokenizer(t_data *data)
{
	t_token	*actual;
	char	type;

	actual = data->first;
	actual->type = COMMAND;
	while (actual->next)
	{
		actual = actual->next;
		type = is_redirection(data, actual->content);
		if (type)
		{
			actual->type = type;
			if (actual->next)
			{
				if (actual->type == PIPE && is_redirection(data, actual->next->content) == 0)
					actual->next->type = COMMAND;
				if (actual->type != PIPE && is_redirection(data, actual->next->content) == 0)
					actual->next->type = FILE;
				actual = actual->next;
			}
		}
		else if (actual->type != STRING_SIMPLE)
			actual->type = STRING;
	}
	/*actual = data->first;
	while(actual)
	{
		printf("%c\n", actual->type);
		actual = actual->next;
	}*/
	return (checker(data));
}