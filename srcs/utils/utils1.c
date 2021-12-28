/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:27:36 by elouchez          #+#    #+#             */
/*   Updated: 2021/12/28 15:34:45 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token *tmp;

	if (!(*alst))
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*ft_lstnew(void *content)
{
	t_token *dest;

	dest = malloc(sizeof(t_token));
	if (!dest)
		return (NULL);
	if (content == NULL)
		dest->content = NULL;
	else
		dest->content = content;
	dest->next = NULL;
	return (dest);
}