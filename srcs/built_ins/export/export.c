/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:56:57 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 20:05:12 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	main_export(t_data *data, char **args)
{
	
}

char	**copy_env(char **str, char **dest, int *i)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (str[len])
		len++;
	while (j < len)
	{
		dest[*i] = malloc((ft_strlen(str[j]) + 1) * sizeof(char));
		//if (!dest[*i])
		//	return (NULL);
		ft_strcpy(dest[*i], str[j]);
		(*i)++;
		j++;
	}
	return (dest);
}

char	**sort_env_atoz(char **str, int len)
{
	char	*tmp;
	int		i;
	int 	j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (str);
}

void	print_export(t_data *data, char **str)
{
	int	i;
	int	j;

	i = 0;
	while(str[i])
	{
		j = 0;
		if (str[i][0] == '_' && str[i][1] == '=')
			i++;
		write(1, "export ", 7);
		while (str[i][j] && str[i][j] != '=')
			ft_putchar_fd(str[i][j++], 1);
		if (str[i][j] == '=')
		{
			write(1, "=\"", 2);
			j++;
			while (str[i][j])
				ft_putchar_fd(str[i][j++], 1);
			write(1, "\"\n", 2);
		}
		else
			write(1, "=\"\"\n", 4);
		i++;
	}
}

void	export_no_arg(t_data *data)
{
	char	**x_env;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (data->envp[len])
		len++;
	x_env = malloc((len + 1) * sizeof(char*));
	//if (!x_env)
		//return (NULL);
	x_env = copy_env(data->envp, x_env, &i);
	x_env[len] = NULL;
	x_env = sort_env_atoz(x_env, len);
	print_export(data, x_env);
}

void	export_args(t_data *data, char **args)
{
	int	len;
	int	i;
	char	**tmp_env;

	main_check(data, args);
	len = 0;
	while (data->envp[len])
		len++;
	i = 0;
	while (data->export.args[i])
		i++;
	len += (i - data->export.equal);
	i = 0;
	tmp_env = malloc((len + 1) * sizeof(char*));
	//if (!x_env)
		//return (NULL);
	copy_equal(data);
	tmp_env = copy_env(data->envp, tmp_env, &i);
	tmp_env = copy_args(data, data->export.args, tmp_env, &i);
	tmp_env[len] = NULL;
	data->envp = tmp_env;
}