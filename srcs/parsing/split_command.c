/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:34:25 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 17:38:31 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_spaces(char *command, int i)
{
	while (command[i] == ' ')
		i++;
	return (i);
}

static int	len_next(char *command, int i)
{
	int	len;

	len = 0;
	while (command[i] != ' ' && command[i] != '\0')
	{
		if (command[i] == '\"' || command[i] == '\'')
		{
			len = get_quoted(command, i - len, command[i]);
			return (len);
		}
		if (command[i] == '<' || command[i] == '>' || command[i] == '|')
			return (len);
		len++;
		i++;
	}
	if (len == 0)
		return (0);
	return (len);
}

static int	check_char(t_data *data, char *command, int i)
{
	int	len;

	if (command[i] == '\"' || command[i] == '\'')
	{
		data->quote_type = command[i];
		len = get_quoted(command, i, command[i]);
	}
	else if (command[i] == '|')
		len = 1;
	else if (command[i] == '>' && command[i + 1] != '>')
		len = 1;
	else if (command[i] == '>' && command[i + 1] == '>')
		len = 2;
	else if (command[i] == '<' && command[i + 1] != '<')
		len = 1;
	else if (command[i] == '<' && command[i + 1] == '<')
		len = 2;
	else
		len = len_next(command, i);
	return (len);
}

static void	split_command_bis(t_data *data, int len, char *elem)
{
	t_token	*new_token;

	if (len != 0)
	{
		new_token = ft_lstnew(data, elem);
		if (data->quote_type == '\'')
			new_token->type = STRING_SIMPLE;
		data->quote_type = '\0';
		ft_lstadd_back(&data->first, new_token);
	}
}

int	split_command(t_data *data, char *command)
{
	int		i;
	int		j;
	int		len;
	char	*elem;

	i = 0;
	while (command[i])
	{
		j = 0;
		elem = NULL;
		i = skip_spaces(command, i);
		len = check_char(data, command, i);
		elem = malloc(sizeof(char) * (len + 1));
		if (!elem)
			alloc_error(data, NULL);
		while (j < len && command[i])
		{
			elem[j] = command[i];
			i++;
			j++;
		}
		elem[j] = '\0';
		split_command_bis(data, len, elem);
	}
	return (0);
}
