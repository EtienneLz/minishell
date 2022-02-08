/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:57:25 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/04 19:08:36 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    env_error(t_data *data, char *str)
{
    ft_putstr_fd("env: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    data->last_ret = 127;
}

void	ft_env(t_data *data, char **args)
{
	int	i;

	data->last_ret = 0;
	if (args[1] != NULL)
	{
		env_error(data, args[1]);
		return ;
	}
	i = 0;
	while (data->envp[i])
		printf("%s\n", data->envp[i++]);
}
