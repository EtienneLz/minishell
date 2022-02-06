/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 07:35:49 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/06 10:19:44 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	splitted_args_free(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	minifree(t_data *data)
{
	ft_lstfree(data);
	splitted_args_free(data->splitted_args);
	free(data->buffer);
	free_tab(data->outfile);
	free_tab(data->infile);
}