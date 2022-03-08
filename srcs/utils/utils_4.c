/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:33:28 by mseligna          #+#    #+#             */
/*   Updated: 2022/02/23 22:54:30 by mseligna         ###   ########.fr       */
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
	if (tab[i])
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

char	***split_arg(t_data *data)
{
	int		size;
	int		i;
	int		j;
	t_token	*actual;
	char	***ret;

	ret = malloc(sizeof(char **) * (data->nb_command + 1));
	if (!ret)
		alloc_error(data, NULL);
	actual = data->first;
	i = 0;
	while (actual && actual->type != COMMAND)
		actual = actual->next;
	while (i < data->nb_command)
	{
		if (i != 0)
			actual = to_command(data->first, i);
		size = 0;
		j = 0;
		while (actual && actual->type != PIPE)
		{
			if (actual->type == RR_ARROW || actual->type == R_ARROW
				|| actual->type == LL_ARROW || actual->type == L_ARROW)
			{
				if (actual->next && actual->next->next)
					actual = actual->next->next;
				else
					break ;
			}
			else
			{
				size++;
				actual = actual->next;
			}	
		}
		actual = data->first;
		if (i != 0)
			actual = to_command(data->first, i);
		else
			while (actual && actual->type != COMMAND)
				actual = actual->next;
		ret[i] = malloc(sizeof(char *) * (size + 1));
		if (!ret[i])
			alloc_error(data, NULL);
		while (actual && actual->type != PIPE)
		{
			if (actual->type == RR_ARROW || actual->type == R_ARROW
				|| actual->type == LL_ARROW || actual->type == L_ARROW)
			{
				if (actual->next && actual->next->next)
					actual = actual->next->next;
				else
					break ;
			}
			else
			{
				if (!(actual->content == NULL && j < size))
				{
					ret[i][j] = actual->content;
					j++;
				}
				actual = actual->next;
			}
		}
		ret[i][j] = NULL;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
