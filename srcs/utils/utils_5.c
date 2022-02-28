/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:38:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 20:38:12 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_size(t_token *actual, int *j, int i)
{
	int	size;

	if (i != 0)
		actual = to_pipe(actual, i);
	size = 0;
	(*j) = 0;
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
	return (size);
}

static t_token	*to_next_oskour(t_data *data, t_token *actual, int i)
{
	actual = data->first;
	if (i != 0)
		actual = to_pipe(actual, i);
	else
		while (actual && actual->type != COMMAND)
			actual = actual->next;
	return (actual);
}

static void	copy_in_tab(t_token *actual, char ****ret, int *j, int i)
{
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
			ret[i][(*j)] = actual->content;
			actual = actual->next;
			(*j)++;
		}
	}
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
		size = get_size(actual, &j, i);
		actual = to_next_oskour(data, actual, i);
		ret[i] = mallocer(&ret[i], sizeof(char *) * (size + 3));
		if (!ret[i])
			alloc_error(data, NULL);
		copy_in_tab(actual, &ret, &j, i);
		ret[i][j] = NULL;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
