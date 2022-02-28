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

t_token	*to_pipe(t_token *actual, int i)
{
	int	w_pipe;

	w_pipe = 0;
	while (actual && w_pipe < i)
	{
		if (actual->type == PIPE)
			w_pipe++;
		actual = actual->next;
	}
	return (actual);
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

	ret = mallocer(&ret, sizeof(char **) * (data->nb_command + 2));
	if (!ret)
		alloc_error(data, NULL);
	actual = data->first;
	i = 0;
	while (actual && actual->type != COMMAND)
		actual = actual->next;
	while (i <= data->nb_pipe + 1)
	{
		if (i != 0)
			actual = to_pipe(actual, i);
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
			actual = to_pipe(actual, i);
		else
			while (actual && actual->type != COMMAND)
				actual = actual->next;
		ret[i] = mallocer(&ret[i], sizeof(char *) * (size + 3));
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
				ret[i][j] = actual->content;
				actual = actual->next;
				j++;
			}
		}
		ret[i][j] = NULL;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
