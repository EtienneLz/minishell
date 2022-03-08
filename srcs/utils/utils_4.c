/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:51:41 by elouchez          #+#    #+#             */
/*   Updated: 2022/03/08 15:51:41 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
			free(tab[i]);
		i++;
	}
	free(tab);
}

t_token	*to_command(t_token *actual, int i)
{
	int	w_com;

	w_com = 0;
	while (actual)
	{
		if (actual->type == COMMAND)
		{
			if (w_com == i)
				return (actual);
			w_com++;
		}
		actual = actual->next;
	}
	return (NULL);
}

t_token	*to_next_command(t_token *actual)
{
	t_token	*act;

	act = actual;
	if (!act)
		return (NULL);
	if (act->next == NULL)
		return (NULL);
	act = act->next;
	while (act && act->type != COMMAND)
		act = act->next;
	return (act);
}
