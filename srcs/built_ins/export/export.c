/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:56:57 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/24 22:45:55 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static int	export_no_arg(t_data *data)
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
		return (1);
	x_env = copy_env(data->envp, x_env, &i);
	if (!x_env)
		return (1);
	x_env[len] = NULL;
	x_env = sort_env_atoz(x_env, len);
	print_export(x_env);
	free_tab(x_env);
	return (0);
}

static int	export_args_bis(t_data *data)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (data->envp[len])
		len++;
	while (data->export.args[i])
		i++;
	len += i;
	return (len);
}

static int	export_args(t_data *data, char **args)
{
	int		len;
	int		i;
	char	**tmp_env;

	export_main_check(data, args);
	len = 0;
	i = 0;
	if (data->export.args != NULL)
	{
		len = export_args_bis(data);
		tmp_env = malloc((len + 1) * sizeof(char *));
		if (!tmp_env)
			return (1);
		tmp_env = copy_env(data->envp, tmp_env, &i);
		if (!tmp_env)
			return (1);
		tmp_env = copy_env(data->export.args, tmp_env, &i);
		tmp_env[len] = NULL;
		data->envp = tmp_env;
	}
	return (0);
}

int	main_export(t_data *data, char **args)
{
	int	ret;

	if (args[1] != NULL)
		ret = export_args(data, args);
	else
		ret = export_no_arg(data);
	if (data->export.args)
		free_tab(data->export.args);
	if (ret == 1)
		alloc_error(data, "export");
	if (data->last_ret == 1000)
		return (0);
	else
		return (data->last_ret);
}
