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

int	nb_next_cmd(t_token	*actual)
{
	char	redir;
	int		i;

	i = 0;
	redir = is_redirection(actual->content);
	while (actual && (redir == PIPE || actual->type == STRING
			|| actual->type == STRING_SIMPLE || actual->type == OPTION
			|| actual->type == COMMAND))
	{
		if (actual->type == COMMAND)
			i++;
		actual = actual->next;
	}
	return (i);
}
