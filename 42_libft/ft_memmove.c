/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 04:23:27 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/13 21:22:33 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*dest1;
	const char	*src1;

	dest1 = (char *)dest;
	src1 = (const char *)src;
	if (dest1 == src1)
		return (dest);
	else if (dest1 > src1)
	{
		src1 = src1 + len - 1;
		dest1 = dest1 + len - 1;
		while (len > 0)
		{
			*dest1 = *src1;
			dest1--;
			src1--;
			len--;
		}
	}
	else
		dest = ft_memcpy(dest1, src1, len);
	return (dest);
}
