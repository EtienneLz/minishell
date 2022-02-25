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
	while (actual)
	{
		if (actual->type == COMMAND && check)
		{
			check = 0;
			actual->prev_pipe = 1;
			tmp->next_pipe = 1;
		}
		if (actual->type == COMMAND)
			tmp = actual;
		if (actual->type == PIPE)
			check = 1;
		actual = actual->next;
	}
}

void	structure(t_data *data)
{
	t_token	*actual;
	t_token	*tmp;

	actual = data->first;
	if (actual->type != COMMAND)
		actual = to_next_command(actual);
	while (actual)
	{
		if (actual->prev && actual->prev->prev
			&& is_arrow(actual->prev->prev->content) == 1)
			copy_name(actual, actual->prev->prev, 1);
		if (actual->prev && is_arrow(actual->prev->content) == 2)
			actual->prev_pipe = 1;
		tmp = actual;
		while (actual && (is_string(actual->type) || actual->type == COMMAND))
			actual = actual->next;
		//structure_bis(data, actual, tmp);
		if (!actual)
			break ;
		if (is_arrow(actual->content) == 1)
			copy_name(tmp, actual, 0);
		if (is_arrow(actual->content) == 2)
			tmp->next_pipe = 1;
		actual = to_next_command(actual);
	}
	check_prev_next(data);
	args_associate(data);
	/*actual = data->first;
	while (actual)
	{
		printf("%c\n", actual->type);
		if (actual->type == COMMAND)
			printf("%s next: %d prev: %d, prev_out: %s, next_out: %s\n", actual->content, actual->next_pipe, actual->prev_pipe, actual->prev_in, actual->next_in);
		actual = actual->next;
	}*/
}
