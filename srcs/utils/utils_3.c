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
	t_token	*act;
	int		len;

	act = data->first;
	while (act)
	{
		if (!is_arrow(act->content))
		{
			len = ft_strlen(act->content);
			if (((act->content[0] == '\'' && act->content[len - 1] == '\'')
					|| (act->content[0] == '\"'
						&& act->content[len - 1] == '\"')) && len == 2)
			{
				free(act->content);
				act->content = NULL;
			}
			else if (act->content[0] == '\''
				&& act->content[len - 1] == '\'')
				act->content = check_quotes(data, act->content);
			else if (act->content[0] == '\"'
				&& act->content[len - 1] == '\"')
				act->content = check_quotes(data, act->content);
		}
		act = act->next;
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
