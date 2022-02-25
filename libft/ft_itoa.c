/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:22:14 by elouchez          #+#    #+#             */
/*   Updated: 2021/07/27 20:38:48 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numb(int nb)
{
	if (nb == 0)
		return (1);
	return (1 + numb(nb / 10));
}

static char	*affect(char *s, int num, int i)
{
	unsigned int	l;

	l = 0;
	if (num == 0)
		*s = num + 48;
	else if (num < 0)
	{
		*s = '-';
		l = num * (-1);
	}
	else
		l = num;
	s[i + 1] = '\0';
	while (l != 0)
	{
		s[i] = l % 10 + 48;
		l = l / 10;
		i--;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dst;

	if (n > 0)
		len = numb(n) - 1;
	else
		len = numb(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	return (affect(dst, n, len - 1));
}
