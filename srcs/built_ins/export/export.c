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

static int	skip_env(char **tab, int i)
{
	if (tab[i][0] == '_' && tab[i][1] == '=')
		i++;
	return (i);
}

static void	print_export(t_data *data, char **tab)
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
	//if (!x_env)
		//return (NULL);
	x_env = copy_env(data->envp, x_env, &i);
	x_env[len] = NULL;
	x_env = sort_env_atoz(x_env, len);
	print_export(data, x_env);
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
		//if (!x_env)
			//return (NULL);
		tmp_env = copy_env(data->envp, tmp_env, &i);
		tmp_env = copy_env(data->export.args, tmp_env, &i);
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
