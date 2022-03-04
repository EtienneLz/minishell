/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:22:00 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:22:00 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	get_valid_args(t_data *data, char *str, int *i)
{
	int	len;

	len = ft_strlen(str);
	if (data->export.args)
	{
		data->export.args[*i] = malloc((len + 1) * sizeof(char));
		if (!(data->export.args[*i]))
			alloc_error(data, "export");
		ft_strcpy(data->export.args[*i], str);
		data->export.valid_args--;
		(*i)++;
		if (data->export.valid_args == 0)
			data->export.args[*i] = NULL;
	}
}

static void	check_export_args_bis(t_data *data, char **args, int i, int *k)
{
	int	j;

	j = 0;
	while (args[i] && args[i][j] && args[i][j] != '='
			&& (ft_isalnum(args[i][j]) || args[i][j] == '_'))
		j++;
	if (args[i] && (!args[i][j] || args[i][j] == '='))
	{
		if (data->export.check != 0 && data->export.valid_args != 0)
			get_valid_args(data, args[i], k);
		else
			data->export.valid_args++;
	}
	else if (args[i])
		if (data->export.check == 0)
			export_error(data, args[i]);
}

static void	check_export_args(t_data *data, char **args)
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
			if (data->export.check == 0 && args[i][0] != '_')
				export_error(data, args[i]);
			i++;
		}
		else if (args[i] && cmp_export_arg(data, args[i]) == 1)
			i++;
		else
		{
			check_export_args_bis(data, args, i, &k);
			i++;
		}
	}
}

void	export_main_check(t_data *data, char **args)
{
	int	valid;
	int	i;

	i = 1;
	while (args[i])
		cmp_export_arg(data, args[i++]);
	data->export.equal = 1;
	check_export_args(data, args);
	data->export.check = 1;
	if (data->export.valid_args > 0)
	{
		valid = data->export.valid_args;
		data->export.args = malloc((valid + 1) * sizeof(char *));
		if (!data->export.args)
			alloc_error(data, "export");
		check_export_args(data, args);
	}
	data->export.check = 0;
}
