/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:13:53 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:13:53 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_bin_path(char *command)
{
	char	*path;
	char	**path_split;
	char	*bin;
	int		i;

	path_split = NULL;
	bin = NULL;
	path = ft_strdup(getenv("PATH"));
	i = 0;
	if (!path)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (command[0] != '/' && ft_strncmp(command, "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		while (path_split[i])
		{
			bin = (char *)ft_calloc(sizeof(char),
					(ft_strlen(path_split[i]) + ft_strlen(command) + 2));
			if (bin == NULL)
				break ;
			ft_strlcat(bin, path_split[i], ft_strlen(bin)
				+ ft_strlen(path_split[i]) + 2);
			ft_strlcat(bin, "/", ft_strlen(bin) + 2);
			ft_strlcat(bin, command, ft_strlen(bin) + ft_strlen(command) + 2);
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
			i++;
		}
		free_tab(path_split);
		return (bin);
	}
	else
	{
		free(path);
		path = NULL;
		return (NULL);
	}
}

static void	pre_check_builtins_2(t_data *data, t_token *actual, int i)
{
	if (!ft_strcmp(actual->args[0], "cd"))
	{
		if (data->nb_command > 1)
			exe_pipe(data, actual, i);
		main_cd(data, actual->args);
	}
	else if (!ft_strcmp(actual->args[0], "unset"))
	{
		exe_pipe(data, actual, i);
		data->ret = main_unset(data, actual->args);
	}
	else if (!ft_strcmp(actual->args[0], "export") && actual->args[1])
	{
		exe_pipe(data, actual, i);
		data->ret = main_export(data, actual->args);
	}
	else
		data->ret = exe_pipe(data, actual, i);
}

void	pre_check_builtins(t_data *data, t_token *actual, int i)
{
	char	*bin;

	if (actual->content[0] == '\0')
	{
		data->ret = 0;
		return ;
	}
	bin = get_bin_path(actual->args[0]);
	if (bin == NULL)
	{
		exe_pipe(data, actual, i);
		data->ret = 127;
	}
	else
	{
		free(bin);
		pre_check_builtins_2(data, actual, i);
	}
}

int	check_built_in(t_data *data, char **args)
{
	int		ret;

	ret = 1;
	if (!ft_strcmp(args[0], "cd"))
		main_cd(data, args);
	else if (!ft_strcmp(args[0], "echo"))
		ret = ft_echo(args);
	else if (!ft_strcmp(args[0], "env"))
		ret = ft_env(data, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(args[0], "unset"))
		ret = main_unset(data, args);
	else if (!ft_strcmp(args[0], "export"))
		ret = main_export(data, args);
	else
		ret = 1000;
	return (ret);
}
