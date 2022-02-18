/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:56:17 by elouchez          #+#    #+#             */
/*   Updated: 2021/12/17 16:08:28 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(t_data *data, char **args, int flag_n)
{
	int	i;

	i = 1;
	if (args[1] == NULL && flag_n == 0)
		ft_putstr_fd("\n", 1);
	else
	{
		while (args[i])
			ft_putstr_fd(args[i++], 1);
		if (!flag_n)
			ft_putstr_fd("\n", 1);
	}
	return (0);
}
