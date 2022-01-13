/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:18:52 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 03:54:21 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_built_in(t_data *data)
{
	char 	*command;
	
	command = data->first->content;
	if (ft_strcmp(command, "cd"))
		cd(data);
	else if (ft_strcmp(command, "echo"))
	{
		if (data->first->next->type == OPTION)
			echo(data, 1);
		else
			echo(data, 0);
	}
	else if (ft_strcmp(command, "env"))
		env(data);
	else if (ft_strcmp(command, "exit"))
		ft_exit(data);
	else if (ft_strcmp(command, "pwd"))
		pwd();
	else if (ft_strcmp(command, "unset"))
		unset(data);
	else if (ft_strcmp(command, "export"))
		export(data);
}

int	execution(t_data *data)
{
	if (check_built_in)
		return (0);
}