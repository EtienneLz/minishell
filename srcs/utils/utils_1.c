/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:27:36 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 17:36:26 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token	*tmp;

	if (!(*alst))
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_token	*ft_lstnew(t_data *data, char *content)
{
	t_token	*dest;

	dest = malloc(sizeof(t_token));
	if (!dest)
		alloc_error(data, NULL);
	dest->type = '\0';
	if (content == NULL)
		dest->content = NULL;
	else
		dest->content = content;
	dest->next = NULL;
	dest->prev = NULL;
	dest->next_in = NULL;
	dest->next_out = NULL;
	dest->next_d_out = NULL;
	dest->prev_in = NULL;
	dest->prev_out = NULL;
	dest->prev_d_out = NULL;
	dest->prev_pipe = 0;
	dest->next_pipe = 0;
	dest->args = NULL;
	dest->id = 0;
	return (dest);
}

void	ft_lstfree(t_data *data)
{
	t_token	*actual;
	t_token	*tmp;

	actual = data->first;
	while (actual->next != NULL)
	{
		tmp = actual->next;
		free(actual->content);
		free(actual);
		actual = tmp;
	}
	free(actual->content);
	free(actual);
}
