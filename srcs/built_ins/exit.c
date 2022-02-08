/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:57:34 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 14:40:15 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *data)
{
	printf("Merci d'avoir utilise Minishell α1.3.0\n");
	minifree(data);
	rl_clear_history();
	exit(0);
}
