/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:56:23 by elouchez          #+#    #+#             */
/*   Updated: 2020/05/16 17:16:13 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		pos;

	i = 0;
	pos = -1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			pos = i;
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	if (pos != -1)
		return ((char *)&s[pos]);
	return (0);
}
