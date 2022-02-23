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
		free(tab[i]);
		i++;
	}
	free(tab);
}

static t_token	*to_pipe(t_data *s_data, t_token *actual, int i)
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

//static void	split_args_bis()

char	***split_arg(t_data *data)
{
	int		size;
	int		i;
	int		j;
	t_token	*actual;
	char	***ret;

	ret = malloc(sizeof(char **) * (data->nb_pipe + 3));
	if (!ret)
		alloc_error(data, NULL);
	actual = data->first;
	i = 0;
	while (actual && actual->type != COMMAND)
		actual = actual->next;
	while (i <= data->nb_pipe + 1)
	{
		if (i != 0)
			actual = to_pipe(data, actual, i);
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
			actual = to_pipe(data, actual, i);
		else
			while (actual && actual->type != COMMAND)
				actual = actual->next;
		ret[i] = malloc(sizeof(char *) * (size + 2));
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
