/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:17:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/14 11:36:07 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(t_data *data)
{
	data->first = NULL;
	data->error = 0;
	data->nb_pipe = 0;
	data->splitted_args = NULL;
	data->buffer = "";
	data->export.args = NULL;
	data->export.valid_args = 0;
	data->export.check = 0;
	data->export.equal = 0;
	data->envp_i = 0;
}