/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 19:51:50 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/13 20:00:45 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*src;
	size_t		i;
	char		search;

	src = (const char *)s;
	search = (char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == search)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
