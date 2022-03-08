/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 05:00:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/03/08 05:00:12 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**init_env(char **envp)
{
	int		i;
	int		size;
	char	**dest;

	i = 0;
	size = 0;
	while (envp[size])
		size++;
	dest = malloc(sizeof(char *) * (size + 1));
	dest = copy_env(envp, dest, &i);
	dest[i] = NULL;
	return (dest);
}
