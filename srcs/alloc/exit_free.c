/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 07:35:49 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 11:51:24 by elouchez         ###   ########.fr       */
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

static void	unlink_heredoc(t_data *data)
{
	char	*file;
	int		i;

	i = 0;
	while (i < data->heredoc_nb)
	{
		file = ft_strdup("tmp/.");
		ft_strlcat(file, ft_itoa(i), 6 + ft_strlen(ft_itoa(i)));
		unlink(file);
		free(file);
		i++;
	}
}

void	minifree(t_data *data)
{
	if (data->first)
		ft_lstfree(data);
	if (data->splitted_args)
		splitted_args_free(data->splitted_args);
	unlink_heredoc(data);
}
