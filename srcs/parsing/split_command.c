/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:34:25 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 06:50:54 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quoted(char *command, int i, char quote)
{
	int	len;

	len = 1;
	i++;
	while (command[i])
	{
		if (command[i] == quote && (command[i + 1] == ' ' || command[i + 1] == '|' || command[i + 1] == '<' || command[i + 1] == '>'))
			break ;
		len++;
		i++;
	}
	return (len + 1);
}

static int	skip_spaces(char *command, int i)
{
	while (command[i] == ' ')
		i++;
	return (i);
}

static int len_next(char *command, int i)
{
	int len;

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

static int	check_char(char *command, int i)
{
	int	len;

	if (command[i] == '\"' || command[i] == '\'')
		len = get_quoted(command, i, command[i]);
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

static	void	lst_show(t_data *data)
{
	t_token *actual;

	actual = data->first;
	while (actual)
	{
		printf("%s\n", actual->content);
		actual = actual->next;
	}
}

int	split_command(t_data *data, char *command)
{
	int		i;
	int		j;
	int		len;
	char	*elem;
	t_token	*new_token;

	i = 0;
	while (command[i])
	{
		j = 0;
		elem = NULL;
		i = skip_spaces(command, i);
		len = check_char(command, i);
		elem = malloc(sizeof(char) * (len + 1));
		if (!elem)
			exit(1);
		while (j < len)
		{
			elem[j] = command[i];
			i++;
			j++;
		}
		if (len != 0)
		{
			elem[j] = '\0';
			new_token = ft_lstnew(elem);
			ft_lstadd_back(&data->first, new_token);
		}
	}
	//lst_show(data);
	return (0);
}
