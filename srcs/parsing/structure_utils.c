/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:07:04 by elouchez          #+#    #+#             */
/*   Updated: 2022/03/10 16:12:24 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_pipe(int *check, t_token *actual, t_token *tmp)
{
	(*check) = 0;
	actual->prev_pipe = 1;
	if (tmp)
		tmp->next_pipe = 1;
}
