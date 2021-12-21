/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:52:15 by elouchez          #+#    #+#             */
/*   Updated: 2021/07/27 20:28:20 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*dest;
	int		i;

	size = ft_strlen(s1);
	dest = malloc(size + 1);
	if (dest == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = (char)s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
