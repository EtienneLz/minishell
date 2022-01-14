/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 18:27:36 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/14 13:18:04 by elouchez         ###   ########.fr       */
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

t_token	*ft_lstnew(char *content)
{
	t_token *dest;

	dest = malloc(sizeof(t_token));
	if (!dest)
		return (NULL);
	dest->type = '0';
	if (content == NULL)
		dest->content = NULL;
	else
		dest->content = content;
	dest->next = NULL;
	return (dest);
}

void	ft_lstfree(t_data *data)
{
	t_token	*actual;
	t_token	*tmp;

	actual = data->first;
	while (actual->next)
	{
		tmp = actual->next;
		free(actual);
		actual = tmp;
	}
	free(actual);
	data->first = NULL;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	***split_arg(t_data *data)
{
	int		size;
	int		i;
	int		j;
	t_token	*actual;
	char 	***ret;

	ret = malloc(sizeof(char**) * (data->nb_pipe + 2));
	if (!ret)
		return (NULL);
	actual = data->first;
	i = 0;
	while (i <= data->nb_pipe)
	{
		size = 0;
		j = 0;
		while (actual && actual->type != PIPE)
		{
			size++;
			actual = actual->next;	
		}
		actual = data->first;
		ret[i] = malloc(sizeof(char*) * (size + 1));
		while (actual && actual->type != PIPE)
		{
			ret[i][j] = actual->content;
			actual = actual->next;
			j++;
		}
		ret[i][j] = NULL;
		i++;
	}
	ret[i] = NULL;
	/*i = 0;
	while(ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			printf("-%s\n", ret[i][j]);
			j++;
		}
		i++;
	}*/

	return (ret);
}

