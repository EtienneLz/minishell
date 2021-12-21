/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 07:28:40 by elouchez          #+#    #+#             */
/*   Updated: 2021/07/27 20:39:36 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*dest;

	dest = malloc(nmemb * size);
	if (dest == NULL)
		return (0);
	ft_memset(dest, 0, size * nmemb);
	return (dest);
}
