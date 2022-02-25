/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 02:49:42 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/13 19:50:31 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*w1;
	unsigned char	*w2;
	size_t			i;

	w1 = (unsigned char *)s1;
	w2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (w1[i] != w2[i])
			return (w1[i] - w2[i]);
		i++;
	}
	return (0);
}
