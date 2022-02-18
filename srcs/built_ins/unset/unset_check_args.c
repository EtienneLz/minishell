/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_check_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 17:36:44 by mseligna          #+#    #+#             */
/*   Updated: 2022/02/18 17:36:44 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	cmp_unset_arg(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (if_equal(data, data->envp[i], str) == 1)
			return (1);
		i++;
	}
	return (0);
}

static void	get_unset_valid_args(t_data *data, char *str, int *i)
{
	int	len;

	len = ft_strlen(str);
	data->unset.args[*i] = malloc((len + 1) * sizeof(char));
	//if (!(data->unset.args[*i]))
		//message erreur + sortie
	ft_strcpy(data->unset.args[*i], str);
	data->unset.valid_args--;
	(*i)++;
	if (data->unset.valid_args == 0)
		data->unset.args[*i] = NULL;
}

static void	check_unset_args_bis(t_data *data, char **args, int i, int *k)
{
	int	j;

	j = 0;
	while (args[i] && args[i][j] && (ft_isalnum(args[i][j])
			|| args[i][j] == '_'))
		j++;
	if (args[i] && !args[i][j] && cmp_unset_arg(data, args[i]) == 1)
	{
		if (data->unset.check != 0 && data->unset.valid_args != 0)
			get_unset_valid_args(data, args[i], k);
		else
			data->unset.valid_args++;
	}
}

static void	check_unset_args(t_data *data, char **args)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (args[i])
	{
		if (args[i] && ((!(ft_isalpha(args[i][0])) && args[i][0] != '_')
				|| (args[i][0] == '_' && args[i][1] == '=')))
		{
			if (data->unset.check == 0 && args[i][0] != '_')
				unset_error(data, args[i]);
		}
		else
			check_unset_args_bis(data, args, i, &k);
		i++;
	}
}

void	unset_main_check(t_data *data, char **args)
{
	int	valid;

	check_unset_args(data, args);
	data->unset.check = 1;
	if (data->unset.valid_args != 0)
	{
		valid = data->unset.valid_args;
		data->unset.args = malloc((valid + 1) * sizeof(char *));
		//if (!tmp)
			//message erreur + sortie
		check_unset_args(data, args);
	}
	data->unset.check = 0;
}
