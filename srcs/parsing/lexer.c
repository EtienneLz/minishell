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
	{
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

void	find_lasts_commands(t_data *data)
{
	t_token	*actual;
	int		check;
	int		fd;

	actual = data->first;
	check = 0;
	while (actual)
	{
		if (is_arrow(actual->content) == 1 && !check)
		{
			while (actual->next && actual->next->next && (actual->next->type == STRING
				|| actual->next->type == STRING_SIMPLE) && is_arrow(actual->next->next->content))
			{
				if (actual->type == R_ARROW || actual->type == RR_ARROW)
				{
					fd = open(actual->next->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
					close(fd);
					actual = actual->next->next;
				}
			}
			if (actual->next && actual->next->next && actual->next->next->type == STRING)
			{
				actual->next->next->type = COMMAND;
				check = 1;
			}
		}
		if (!actual)
			break ;
		while (actual && actual->type != PIPE)
			actual = actual->next;
		if (actual && actual->type == PIPE)
			if (actual->next)
			{
				actual = actual->next;
				check = 0;
			}
		
	}
}

int	lexer(t_data *data)
{
	t_token	*actual;
	char	type;

	actual = data->first;
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
	/*actual = data->first;
	
	infiles_name(data);
	while (actual)
	{
		printf("t = %c\n", actual->type);
		if (is_redirection(actual->content) && !actual->next)
		{
			print_error(data, "syntax error near unexpected token `newline\'\n");
			return (1);
		}
			
		actual = actual->next;
	}*/
	find_lasts_commands(data);
	counter(data);
	return (0);
}
