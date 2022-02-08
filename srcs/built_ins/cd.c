/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:56:29 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 16:37:24 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    cd_error(t_data *data, char *str)
{
    ft_putstr_fd("minishell: cd: ", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    data->last_ret = 1;
}

void	change_pwd_vars(t_data *data, char *oldpwd, char *pwd)
{
	char	*find;
	char	*find_old;
	int		i;
	int		checkpwd;
	int		old;

	find = "PWD";
	find_old = "OLDPWD";
	i = 0;
	checkpwd = 0;
	old = 0;
	while (data->envp[i])
	{
		if (strncmp(data->envp[i], find, 3) == 0)
		{
			data->envp[i] = join_arg(data->envp[i], pwd);
			checkpwd = 1;
		}
		if (strncmp(data->envp[i], find_old, 6) == 0)
		{
			data->envp[i] = join_arg(data->envp[i], oldpwd);
			old = i;
		}
		i++;
	}
	if (checkpwd == 0)
		data->envp[old] = join_arg(data->envp[old], "=");
}

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

char	*if_tilde(t_data *data, char *arg)
{
	char	*home;
	char	*new_dir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_strlen(arg) == 1 || (arg[0] == 'c' && arg[1] == 'd'))
		return (data->cd.home);
	new_dir = malloc(ft_strlen(data->cd.home) + ft_strlen(arg));
	//if (!new_dir)
			//erreur
	new_dir = cd_join(data->cd.home, arg, new_dir);
	return (new_dir);
}

void	do_cd(t_data *data, char **args, int len)
{
	char path[PATH_MAX];
	char	*pwd;
	char *str;

	getcwd(path, PATH_MAX);
	pwd = getenv("PWD");
	if (len == 1)
	{
		str = if_tilde(data, args[0]);
		data->cd.ret = chdir(str);
	}
	else
	{
		if (args[1][0] == '/')
			data->cd.ret = chdir(args[1]);
		else if (args[1][0] == '~')
		{
			str = if_tilde(data, args[1]);
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
	}
	if(data->cd.ret != 0)
		cd_error(data, args[1]);
	else
	{
		getcwd(path, PATH_MAX);
		change_pwd_vars(data, pwd, path);
	}
}

int	main_cd(t_data * data, char **args)
{
	int	len;
	char	*new_dir;

	len = 0;
	data->last_ret = 0;
	while (args[len])
		len++;
	do_cd(data, args, len);
	return (data->cd.ret);
}