/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:32:08 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 09:32:08 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe(t_token	*actual)
{
	if (actual->next)
		actual = actual->next;
	else
		return (0);
	while (actual && actual->type == STRING || actual->type == STRING_SIMPLE
		|| actual->type == OPTION)
	{
		if (actual->next == NULL)
			return (0);
		if (actual->next->type == PIPE)
			return (1);
		actual = actual->next;
	}
	return (0);
}

t_token	*to_next_command(t_token *actual)
{
	t_token	*act;

	act = actual;
	if (act->next == NULL)
		return (NULL);
	act = act->next;
	while (act && act->type != COMMAND)
	{
		act = act->next;
	}
	return (act);
}

void	check_exit(t_data *data)
{
	t_token	*actual;
	int		i;

	actual = data->first;
	i = 0;
	while (actual)
	{
		if (actual->type == COMMAND)
		{
			i++;
			if (!ft_strcmp(actual->content, "exit"))
				ft_exit(data, data->splitted_args[i - 1]);
		}
		actual = actual->next;
	}
}

void	check_quotes_bis(char quote, int *len, int *i)
{
	if (quote)
	{
		(*len)--;
		*i = 1;
	}
}

char	*check_quotes(char *str)
{
	int		i;
	int		len;
	char	quote;
	char	*dest;

	i = 0;
	quote = 0;
	len = ft_strlen(str) + 1;
	if (str[0] == '\"')
		quote = '\"';
	else if (str[0] == '\'')
		quote = '\'';
	check_quotes_bis(quote, &len, &i);
	if (str[len - 2] == quote)
		len--;
	dest = malloc(sizeof(char) * len);
	while (i < len - 1)
	{
		dest[i - 1] = str[i];
		i++;
	}
	dest[i - 1] = '\0';
	free(str);
	return (dest);
}
