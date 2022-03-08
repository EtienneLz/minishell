/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structurationinger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:29:33 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/16 10:29:33 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_name(t_token *actual, t_token *to_copy, int dir)
{
	if (dir)
	{
		if (to_copy->type == L_ARROW)
			actual->prev_in = ft_strdup(to_copy->next->content);
		if (to_copy->type == LL_ARROW)
			actual->prev_in = ft_strdup(to_copy->next->content);
		if (to_copy->type == R_ARROW)
			actual->prev_out = ft_strdup(to_copy->next->content);
		if (to_copy->type == RR_ARROW)
			actual->prev_d_out = ft_strdup(to_copy->next->content);
	}
	else if (!dir)
	{
		if (to_copy->type == L_ARROW)
			actual->next_in = ft_strdup(to_copy->next->content);
		if (to_copy->type == LL_ARROW)
			actual->next_in = ft_strdup(to_copy->next->content);
		if (to_copy->type == R_ARROW)
			actual->next_out = ft_strdup(to_copy->next->content);
		if (to_copy->type == RR_ARROW)
			actual->next_d_out = ft_strdup(to_copy->next->content);
	}
}

static void	args_associate(t_data *data)
{
	int		i;
	t_token	*actual;

	i = 0;
	actual = data->first;
	while (actual)
	{
		if (actual->type == COMMAND)
		{
			actual->id = i;
			actual->args = data->splitted_args[i];
			i++;
		}
		actual = actual->next;
	}
}

static void	check_prev_next(t_data *data)
{
	t_token	*actual;
	t_token	*tmp;
	int		check;

	actual = data->first;
	check = 0;
	tmp = NULL;
	while (actual)
	{
		if (actual->type == COMMAND && check)
		{
			check = 0;
			actual->prev_pipe = 1;
			if (tmp)
				tmp->next_pipe = 1;
		}
		if (actual->type == COMMAND)
			tmp = actual;
		if (actual->type == PIPE && tmp)
			check = 1;
		actual = actual->next;
	}
	args_associate(data);
}

static t_token	*structure_2(t_token *actual, t_token *tmp)
{
	while (actual && actual->next && actual->next->next
		&& is_arrow(actual->content) == 1)
	{
		copy_name(tmp, actual, 0);
		actual = actual->next->next;
	}
	if (actual && actual->next && !actual->next->next
		&& is_arrow(actual->content) == 1)
		copy_name(tmp, actual, 0);
	return (actual);
}

void	structure(t_data *data)
{
	t_token	*actual;
	t_token	*tmp;

	actual = structure_norm(data);
	while (actual)
	{
		if (actual->prev && actual->prev->prev
			&& is_arrow(actual->prev->prev->content) == 1)
			copy_name(actual, actual->prev->prev, 1);
		if (actual->prev && is_arrow(actual->prev->content) == 2)
			actual->prev_pipe = 1;
		tmp = actual;
		while (actual && actual->next && (!is_string(actual->type)
				|| actual->type == COMMAND)
			&& is_arrow(actual->next->content) != 1)
			actual = actual->next;
		if (actual && actual->next && is_arrow(actual->next->content) == 1)
			actual = actual->next;
		actual = structure_2(actual, tmp);
		if (actual && is_arrow(actual->content) == 2)
			tmp->next_pipe = 1;
		actual = to_next_command(actual);
	}
	check_prev_next(data);
}
