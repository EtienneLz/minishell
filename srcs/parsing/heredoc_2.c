/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 04:25:21 by elouchez          #+#    #+#             */
/*   Updated: 2022/03/10 04:25:21 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*concanate(int j, char *src)
{
	char	*num;
	int		len;
	char	*dest;
	int		i;

	num = ft_itoa(j);
	i = 0;
	len = ft_strlen(num);
	dest = mallocer(&dest, sizeof(char) * (ft_strlen(src) + len + 1));
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	len = 0;
	while (num[len])
	{
		dest[i] = num[len];
		len++;
		i++;
	}
	dest[i] = '\0';
	free(num);
	return (dest);
}

void	here_free(t_data *data, char *file, char **sep)
{
	minifree(data);
	free(file);
	free(sep);
	if (data->envp)
		free_tab(data->envp);
}

int	here_break(t_data *data, char *buffer, int *code, char **sep)
{
	if (!buffer)
	{
		if (g_pid == 128)
		{
			(*code) = 128;
			return (1);
		}
		printf("minishell: warning: heredoc delimited by EOF ");
		printf("(wanted `%s\')\n", sep[data->heredoc_nb]);
		return (1);
	}
	return (0);
}
