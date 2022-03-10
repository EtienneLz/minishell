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

static int	get_size(t_data *data, t_token *actual, int i)
{
	int	size;

	if (i != 0)
		actual = to_command(data->first, i);
	size = 0;
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

static t_token	*actual_command(t_data *data, int i)
{
	t_token	*actual;

	actual = data->first;
	if (i != 0)
		actual = to_command(data->first, i);
	else
		while (actual && actual->type != COMMAND)
			actual = actual->next;
	return (actual);
}

static char	**return_arg(t_data *data, t_token *actual, int size)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (!ret)
		alloc_error(data, NULL);
	while (actual && actual->type != PIPE)
	{
		if (is_arrow(actual->content) == 1)
		{
			if (actual->next && actual->next->next)
				actual = actual->next->next;
			else
				break ;
		}
		else
		{
			if (!(actual->content == NULL && i < size))
				ret[i++] = actual->content;
			actual = actual->next;
		}
	}
	ret[i] = NULL;
	return (ret);
}	

char	***split_arg(t_data *data)
{
	int		i;
	t_token	*actual;
	char	***ret;
	int		size;

	ret = malloc(sizeof(char **) * (data->nb_command + 1));
	if (!ret)
		alloc_error(data, NULL);
	actual = data->first;
	i = 0;
	while (actual && actual->type != COMMAND)
		actual = actual->next;
	while (i < data->nb_command)
	{
		size = get_size(data, actual, i);
		actual = actual_command(data, i);
		ret[i] = return_arg(data, actual, size);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	*alloc_split(int *j)
{
	(*j) = 0;
	return (NULL);
}
