/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:17:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/07 19:56:22 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init(t_data *data)
{
	data->first = NULL;
	data->export.args = NULL;
	data->export.valid_args = 0;
	data->export.check = 0;
}