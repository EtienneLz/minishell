/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:57:12 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/24 23:35:21 by mseligna         ###   ########.fr       */
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
			//if (!dest[*i])
			//	return (NULL);
			ft_strcpy(dest[*i], data->envp[j]);
			(*i)++;
			j++;
		}
	}
	return (dest);
}

static void	unset_args(t_data *data, char **args)
{
	int		len;
	int		i;
	char	**tmp_env;

	len = 0;
	data->unset.is_unset = 1;
	unset_main_check(data, args);
	if (data->unset.args != NULL)
	{
		while (data->envp[len])
			len++;
		i = 0;
		while (data->unset.args[i])
			i++;
		len -= i;
		i = 0;
		tmp_env = malloc((len + 1) * sizeof(char *));
		//if (!x_env)
			//return (NULL);
		tmp_env = copy_unset_env(data, tmp_env, &i);
		tmp_env[len] = NULL;
		data->envp = tmp_env;
		free_tab(data->unset.args);
		data->unset.is_unset = 0;
	}
}

/**
  * si erreur de malloc (check erreur?)
  * si tout bon ret export = 0 sinon ret = 1;
  **/

int	main_unset(t_data *data, char **args)
{
	data->last_ret = 0;
	if (args[1] != NULL)
		unset_args(data, args);
	return (data->last_ret);
}
