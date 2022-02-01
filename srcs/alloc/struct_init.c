/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:17:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/24 22:23:51 by mseligna         ###   ########.fr       */
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
	data->unset.is_unset = 0;
	data->unset.check = 0;
	data->unset.valid_args = 0;
	data->unset.args = NULL;
	data->cd.home = NULL;
}
