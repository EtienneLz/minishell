/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:35:22 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/13 21:06:18 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *dest, size_t n)
{
	size_t		i;
	char		*ensac;

	ensac = (char *)dest;
	i = 0;
	while (i < n)
	{
		ensac[i] = '\0';
		i++;
	}
}
