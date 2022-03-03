/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:22:19 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:22:19 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	skip_env(char **tab, int i)
{
	if (tab[i][0] == '_' && tab[i][1] == '=')
		i++;
	return (i);
}

static void	print_export(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		i = skip_env(tab, i);
		if (!tab[i])
			break ;
		write(1, "export ", 7);
		while (tab[i][j] && tab[i][j] != '=')
			ft_putchar_fd(tab[i][j++], 1);
		if (tab[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while (tab[i][j])
				ft_putchar_fd(tab[i][j++], 1);
			write(1, "\"\n", 2);
		}
		else
			write(1, "=\"\"\n", 4);
		i++;
	}
}

static void	export_no_arg(t_data *data)
{
	char	**x_env;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (data->envp[len])
		len++;
	x_env = malloc((len + 1) * sizeof(char *));
	if (!x_env)
		alloc_error(data, "export");
	x_env = copy_env(data, data->envp, x_env, &i);
	x_env[len] = NULL;
	x_env = sort_env_atoz(x_env, len);
	print_export(x_env);
	free_tab(x_env);
}

static void	export_args(t_data *data, char **args)
{
	int		len;
	int		i;
	char	**tmp_env;

	export_main_check(data, args);
	len = 0;
	while (data->envp[len])
		len++;
	i = 0;
	if (data->export.args != NULL)
	{
		while (data->export.args[i])
			i++;
		len += i;
		i = 0;
		tmp_env = malloc((len + 1) * sizeof(char *));
		if (!tmp_env)
			alloc_error(data, "export");
		tmp_env = copy_env(data, data->envp, tmp_env, &i);
		tmp_env = copy_env(data, data->export.args, tmp_env, &i);
		tmp_env[len] = NULL;
		data->envp = tmp_env;
		free_tab(data->export.args);
	}
}

int	main_export(t_data *data, char **args)
{
	data->last_ret = 0;
	if (args[1] != NULL)
		export_args(data, args);
	else
		export_no_arg(data);
	return (data->last_ret);
}
