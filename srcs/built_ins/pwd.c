/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:56:39 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/20 16:20:34 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_data *data)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_putendl_fd(path, STDOUT);
	return (0);
}
