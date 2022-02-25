/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:38:54 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/13 21:50:35 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		lm;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	if (big == NULL && len == 0)
		return (NULL);
	while (big[i] && len > 0)
	{
		lm = len;
		j = 0;
		while (big[i + j] == little[j] && lm > 0)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
			lm--;
		}
		i++;
		len--;
	}
	return (NULL);
}
