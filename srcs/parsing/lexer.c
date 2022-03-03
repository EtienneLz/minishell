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

char	is_redirection(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if (!ft_strcmp(str, "<"))
		return (L_ARROW);
	else if (!ft_strcmp(str, ">"))
		return (R_ARROW);
	else if (!ft_strcmp(str, "<<"))
		return (LL_ARROW);
	else if (!ft_strcmp(str, ">>"))
		return (RR_ARROW);
	return (0);
}

static void	counter(t_data *data)
{
	t_token	*actual;

	actual = data->first;
	while (actual)
	{
		if (actual->type == L_ARROW)
			data->nb_infiles++;
		else if (actual->type == LL_ARROW)
			data->heredoc++;
		else if (actual->type == R_ARROW)
			data->nb_outfiles++;
		else if (actual->type == RR_ARROW)
			data->nb_outfiles++;
		else if (actual->type == PIPE)
			data->nb_pipe++;
		else if (actual->type == COMMAND)
			data->nb_command++;
		actual = actual->next;
	}	
}

static void	find_lasts_commands(t_data *data)
{
	t_token	*actual;
	int		check;

	actual = data->first;
	check = 0;
	while (actual)
	{
		while (actual->next && is_arrow(actual->content) == 1 && !check)
		{
			actual = lasts_commands_2(actual, &check);
		}
		while (actual && actual->type != PIPE)
			actual = actual->next;
		if (actual && actual->type == PIPE)
		{
			if (actual->next)
			{
				actual = actual->next;
				check = 0;
			}
			else
				return ;
		}
	}
}

void	create_files(t_data *data)
{
	t_token	*actual;
	int		fd;

	fd = 0;
	actual = data->first;
	while (actual)
	{
		if (!actual->next && is_arrow(actual->content) == 1)
			return ;
		if (actual->type == R_ARROW || actual->type == RR_ARROW)
		{
			if (actual->type == R_ARROW && !is_arrow(actual->next->content))
				fd = open(actual->next->content,
						O_CREAT | O_RDWR | O_TRUNC, 0644);
			else if (actual->type == RR_ARROW
				&& !is_arrow(actual->next->content))
				fd = open(actual->next->content,
						O_CREAT | O_RDWR | O_APPEND, 0644);
			if (fd < 0)
				perror("minishell");
			else if (fd != 0)
				close(fd);
		}
		actual = actual->next;
	}
	counter(data);
}

int	lexer(t_data *data)
{
	t_token	*actual;
	char	type;

	actual = data->first;
	if (!actual)
		return (1);
	actual->type = is_redirection(actual->content);
	if (actual->type == 0)
		actual->type = COMMAND;
	while (actual->next)
	{
		actual = actual->next;
		type = is_redirection(actual->content);
		if (type)
		{
			actual->type = type;
			if (actual->next)
				actual = lexer_2(actual);
		}
		else if (actual->type != STRING_SIMPLE)
			actual->type = STRING;
	}
	find_lasts_commands(data);
	final_lex(data);
	return (0);
}
