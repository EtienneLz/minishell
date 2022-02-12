/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:27:37 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 17:35:57 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	is_redirection(t_data *data, char *str)
{
	if (!ft_strcmp(str, "|"))
	{
		data->nb_pipe++;
		return (PIPE);
	}
	else if (!ft_strcmp(str, "<"))
	{
		return (L_ARROW);
	}
	else if (!ft_strcmp(str, ">"))
	{
		return (R_ARROW);
	}
	else if (!ft_strcmp(str, "<<"))
		return (LL_ARROW);
	else if (!ft_strcmp(str, ">>"))
	{
		return (RR_ARROW);
	}
	return (0);
}

static void	counter(t_data *data, char type)
{
	if (type == L_ARROW)
		data->nb_infiles++;
	else if (type == LL_ARROW)
		data->nb_infiles++;
	else if (type == R_ARROW)
		data->nb_outfiles++;
	else if (type == RR_ARROW)
		data->nb_outfiles++;
}

static void	infiles_name(t_data *data)
{
	t_token	*actual;
	int		i;
	int		j;

	data->infile = malloc(sizeof(char*) * (data->nb_infiles + 1));
	data->outfile = malloc(sizeof(char*) * (data->nb_outfiles + 2));
	actual = data->first;
	i = 0;
	j = 0;
	while (actual)
	{
		if ((actual->type == R_ARROW || actual->type == RR_ARROW) && actual->next)
		{
			data->outfile[j] = actual->next->content;
			if (actual->type == RR_ARROW)
				data->last_out = 2;
			else
				data->last_out = 1;
			if (actual->next->next && (is_redirection(data, actual->next->next->content) == 0))
				actual->next->next->type = COMMAND;
			j++;
		}
		else if ((actual->type == L_ARROW || actual->type == LL_ARROW) && actual->next)
		{
			data->infile[i] = actual->next->content;
			if (actual->next->next && (is_redirection(data, actual->next->next->content) == 0))
				actual->next->next->type = COMMAND;
			i++;
		}
		actual = actual->next;
	}
	data->infile[i] = NULL;
	data->outfile[j] = NULL;
}

static int	checker(t_data *data)
{
	t_token	*actual;
	t_token	*next;

	actual = data->first;
	next = actual->next;
	while (actual && actual->next)
	{
		if (actual->type == COMMAND && next->type == STRING)
			if (next->content[0] == '-')
				next->type = OPTION;
		if ((actual->type != STRING || actual->type != STRING_SIMPLE) && actual->type == next->type)
			return (1);
		actual = next;
		next = actual->next;
	}
	return (0);
}

int	lexer(t_data *data)
{
	t_token	*actual;
	char	type;

	actual = data->first;
	actual->type = is_redirection(data, actual->content);
	if (actual->type == 0)
		actual->type = COMMAND;
	while (actual->next)
	{
		actual = actual->next;
		type = is_redirection(data, actual->content);
		if (type)
		{
			actual->type = type;
			if (actual->next)
			{

				if (actual->type == PIPE && actual->next->type == 0)
					actual->next->type = COMMAND;
				else
					actual->next->type = STRING;
				actual = actual->next;
			}
		}
		else if (actual->type != STRING_SIMPLE)
			actual->type = STRING;
	}
	actual = data->first;
	while (actual)
	{
		//printf("t = %c\n", actual->type);
		counter(data, actual->type);
		actual = actual->next;
	}
	infiles_name(data);
	return (0);
}
