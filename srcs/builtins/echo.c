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

void	echo(char *s, int flag_n)
{
	int	i;

	i = 0;
	if (s == NULL && flag_n == 0)
		ft_putstr_fd("\n", 1);
	else
	{
		ft_putstr_fd(s, 1);
		if (!flag_n)
			ft_putstr_fd("\n", 1);
	}
}