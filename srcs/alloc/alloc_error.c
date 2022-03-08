/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:09:34 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:09:34 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_args(t_data *data)
{
	if (data->export.args != NULL)
		free_tab(data->export.args);
	if (data->unset.args != NULL)
		free_tab(data->unset.args);
}

void	alloc_error(t_data *data, char *cmd)
{
	if (data->last_ret != 1000)
	{
		ft_putstr_fd("minishell: ", 2);
		if (cmd != NULL)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putstr_fd(": memory allocation failed\n", 2);
	}
	data->last_ret = 1;
}
