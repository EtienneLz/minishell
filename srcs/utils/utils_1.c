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
	dest->type = '\0';
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

static t_token	*to_pipe(t_data *s_data, t_token *actual, int i)
{
	int	w_pipe;

	w_pipe = 0;
	while (actual && w_pipe < i)
	{
		if (actual->type == PIPE)
			w_pipe++;
		actual = actual->next;
	}
	return (actual);
}

char	***split_arg(t_data *data)
{
	int		size;
	int		i;
	int		j;
	t_token	*actual;
	char 	***ret;

	ret = malloc(sizeof(char**) * (data->nb_pipe + 3));
	if (!ret)
		return (NULL);
	actual = data->first;
	i = 0;
	while (actual && actual->type != COMMAND)
		actual = actual->next;
	while (i <= data->nb_pipe + 1)
	{
		if (i != 0)
			actual = to_pipe(data, actual, i);
		size = 0;
		j = 0;
		while (actual && actual->type != PIPE)
		{
			if (actual->type == RR_ARROW || actual->type == R_ARROW || actual->type == LL_ARROW || actual->type == L_ARROW)
				break ;
			size++;
			actual = actual->next;	
		}
		actual = data->first;
		if (i != 0)
			actual = to_pipe(data, actual, i);
		else
			while (actual && actual->type != COMMAND)
				actual = actual->next;
		ret[i] = malloc(sizeof(char*) * (size + 2));
		while (actual && actual->type != PIPE)
		{
			if (actual->type == RR_ARROW || actual->type == R_ARROW || actual->type == LL_ARROW || actual->type == L_ARROW)
				break ;
			ret[i][j] = actual->content;
			actual = actual->next;
			j++;
		}
		ret[i][j] = NULL;
		i++;
	}
	ret[i] = NULL;
	/*i = 0;
	j = 0;
	printf("bonjour\n");
	while (ret[i])
	{
		while(ret[i][j])
		{
			printf("ss%s ", ret[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}*/
	return (ret);
}

