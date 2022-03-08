/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:22:42 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:22:42 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	exclude_equal(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->unset.args[i])
	{
		if (if_equal(data, str, data->unset.args[i]))
			return (1);
		i++;
	}
	return (0);
}

static char	**copy_unset_env(t_data *data, char **dest, int *i)
{
	int	j;

	j = 0;
	while (data->envp[j])
	{
		if (exclude_equal(data, data->envp[j]))
			j++;
		else
		{
			dest[*i] = malloc((ft_strlen(data->envp[j]) + 1) * sizeof(char));
			if (!dest[*i])
			{
				free_tab(dest);
				return (NULL);
			}
			ft_strcpy(dest[*i], data->envp[j]);
			(*i)++;
			j++;
		}
	}
	return (dest);
}

static int	unset_args_bis(t_data *data)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (data->envp[len])
		len++;
	while (data->unset.args[i])
		i++;
	len -= i;
	return (len);
}

static int	unset_args(t_data *data, char **args)
{
	int		len;
	int		i;
	char	**tmp_env;

	len = 0;
	data->unset.is_unset = 1;
	unset_main_check(data, args);
	if (data->unset.args != NULL)
	{
		len = unset_args_bis(data);
		i = 0;
		tmp_env = malloc((len + 1) * sizeof(char *));
		if (!tmp_env)
			return (1);
		tmp_env = copy_unset_env(data, tmp_env, &i);
		tmp_env[len] = NULL;
		free_tab(data->envp);
		free(data->envp);
		if (tmp_env)
			data->envp = tmp_env;
	}
	return (0);
}

int	main_unset(t_data *data, char **args)
{
	int	ret;

	ret = 0;
	if (args[1] != NULL)
		ret = unset_args(data, args);
	if (data->unset.args)
	{
		free_tab(data->unset.args);
		free(data->unset.args);
	}
	data->unset.is_unset = 0;
	if (ret == 1)
		alloc_error(data, "unset");
	if (data->last_ret == 1000)
		return (0);
	else
		return (data->last_ret);
}
