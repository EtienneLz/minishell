/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 05:11:02 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/15 05:11:02 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_arrow(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (2);
	else if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	is_string(char type)
{
	if (type == STRING || type == STRING_SIMPLE || type == OPTION)
		return (1);
	return (0);
}

t_token	*to_prev_command(t_token *actual)
{
	t_token	*act;

	act = actual;
	if (act->prev == NULL)
		return (NULL);
	act = act->prev;
	while (act && act->type != COMMAND)
		act = act->prev;
	return (act);
}

void	remove_quotes(t_data *data)
{
	t_token	*actual;
	int		len;

	actual = data->first;
	while (actual)
	{
		if (!is_arrow(actual->content))
		{
			len = ft_strlen(actual->content);
			if (actual->content[0] == '\'' && actual->content[len - 1] == '\'')
				actual->content = check_quotes(data, actual->content);
			else if (actual->content[0] == '\"'
				&& actual->content[len - 1] == '\"')
				actual->content = check_quotes(data, actual->content);
		}
		actual = actual->next;
	}
}

t_token	*structure_norm(t_data *data)
{
	t_token	*actual;

	actual = data->first;
	if (actual->type != COMMAND)
		actual = to_next_command(actual);
	return (actual);
}
