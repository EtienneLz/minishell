/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:22:55 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:22:55 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_zero(char *str)
{
	if (ft_strlen(str) > 2)
		return (-1);
	if (ft_strlen(str) == 1)
	{
		if (str[0] != '0')
			return (-1);
		else
			return (0);
	}
	if (str[0] != '-' && str[0] != '+')
		return (-1);
	else
		if (str[1] == '0')
			return (0);
	return (2);
}

void	non_numeric_arg(t_data *data, char *arg)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	data->last_ret = 255;
	minifree(data);
	if (data->envp && data->is_export)
	{
		free_tab(data->envp);
		free(data->envp);
	}
	exit(data->last_ret);
}

void	ft_do_exit(t_data *data, int nb)
{
	ft_putstr_fd("exit\n", 1);
	data->last_ret = nb;
	minifree(data);
	if (data->envp && data->is_export)
	{
		free_tab(data->envp);
		free(data->envp);
	}
	exit(data->last_ret);
}

void	ft_exit_bis(t_data *data, char **args, int i)
{
	long long	nb;

	while (args[1][i])
	{
		if (i == 0 && (args[1][i] == '-' || args[1][i] == '+'))
			i++;
		if (!(ft_isdigit(args[1][i])))
			non_numeric_arg(data, args[1]);
		i++;
	}
	nb = ft_atoi(args[1]);
	if (nb == 0)
		non_numeric_arg(data, args[1]);
	else if (nb > 255 || nb < 0)
		ft_do_exit(data, nb % 256);
	else
		ft_do_exit(data, nb);
}

void	ft_exit(t_data *data, char **args)
{
	int			i;

	i = 0;
	if (!args)
		ft_do_exit(data, 0);
	while (args[i])
		i++;
	if (i == 1)
		ft_do_exit(data, 0);
	if (i > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else
	{
		if (if_zero(args[1]) == '0')
			ft_do_exit(data, 0);
		else
		{
			i = 0;
			ft_exit_bis(data, args, i);
		}
	}
}
