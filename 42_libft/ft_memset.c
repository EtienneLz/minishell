/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:35:47 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/13 19:50:42 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*ensac;
	size_t			i;

	i = 0;
	ensac = dest;
	while (i < n)
	{
		ensac[i] = c;
		i++;
	}
	return (dest);
}
