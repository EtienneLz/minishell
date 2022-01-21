/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:56:29 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/21 19:06:28 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_join(char *dir, char *arg, char *new_dir)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dir[i])
	{
		new_dir[i] = dir[i];
		i++;
	}
	if (arg[0] != '~')
		new_dir[i++] = '/';
	else
		j = 1;
	while (arg[j])
		new_dir[i++] = arg[j++];
	new_dir[i] = '\0';
	return (new_dir);
}

char	*if_tilde(char *arg)
{
	char	*home;
	char	*new_dir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	home = getenv("HOME");
	if (ft_strlen(arg) == 1)
		return (home);
	new_dir = malloc(ft_strlen(home) + ft_strlen(arg));
	//if (!new_dir)
			//erreur
	new_dir = cd_join(home, arg, new_dir);
	return (new_dir);
}

void	do_cd(t_data *data, char **args)
{
	char path[PATH_MAX];
	char *str;

	getcwd(path, PATH_MAX);
	if (args[1][0] == '/')
		data->cd.ret = chdir(args[1]);
	else if (args[1][0] == '~')
	{
		str = if_tilde(args[1]);
		data->cd.ret = chdir(str);
	}
	else
	{
		str = malloc(ft_strlen(path) + ft_strlen(args[1]) + 2);
		//if (!str)
			//erreur
		str = cd_join(path, args[1], str);
		data->cd.ret = chdir(str);
	}
	//if (data->cd.ret != 0)
	//	return ;//message d'erreur, chemin non existant
	
}

int	main_cd(t_data * data, char **args)
{
	int	len;

	len = 0;
	while (args[len])
		len++;
	if (len != 2)
		return (1);
	if (args[1] != NULL)
		do_cd(data, args);
	return (data->cd.ret);
}