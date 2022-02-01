/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:17:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/24 16:50:22 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(t_data *data)
{
	data->first = NULL;
	data->actual = NULL;
	data->error = 0;
	data->nb_pipe = 0;
	data->splitted_args = NULL;
	data->buffer = "";
	data->quote_type = '\0';
	data->export.args = NULL;
	data->export.valid_args = 0;
	data->export.check = 0;
	data->export.equal = 0;
	data->envp_i = 0;
	data->command_nb = 0;
	data->pid = 0;
}
