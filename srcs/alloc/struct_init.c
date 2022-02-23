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
	g_pid = 0;
	data->tmpin = 0;
	data->tmpout = 0;
	data->unset.is_unset = 0;
	data->unset.check = 0;
	data->unset.valid_args = 0;
	data->unset.args = NULL;
	data->cd.home = NULL;
	data->nb_infiles = 0;
	data->heredoc = 0;
	data->nb_outfiles = 0;
	data->last_out = 0;
	data->tmp_var = NULL;
	data->nb_command = 0;
	data->infile = NULL;
	data->outfile = NULL;
}

void	reset(t_data *data)
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
	g_pid = 0;
	data->tmpin = 0;
	data->tmpout = 0;
	data->unset.is_unset = 0;
	data->unset.check = 0;
	data->unset.valid_args = 0;
	data->unset.args = NULL;
	data->nb_infiles = 0;
	data->nb_outfiles = 0;
	data->last_out = 0;
	data->tmp_var = NULL;
}
