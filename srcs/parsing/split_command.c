/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:34:25 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/03 15:03:21 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_quoted(char *command, int i, char quote)
{
	int	len;

	len = 0;
	while (command[i] != quote)
	{
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
		len++;
		i++;
	}
	printf("%d\n", len);
	return (len + 1);
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

void	split_command(t_data *data, char *command)
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
		if (command[i] == '\"' || command[i] == '\'')
			len = get_quoted(command, i, command[i]);
		else
			len = len_next(command, i);
		elem = malloc(sizeof(char) * len);
		if (!elem)
			exit(1);
		while (j < len)
		{
			elem[j] = command[i];
			i++;
			j++;
		}
		elem[j] = '\0';
		new_token = ft_lstnew(elem);
		ft_lstadd_back(&data->first, new_token);
	}
	lst_show(data);
}
