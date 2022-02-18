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

#include "../../../includes/minishell.h"

static char	*get_env_val(t_data *data, char *str)
{
	char	*ret;
	char	*tmp;

	tmp = check_exist(data, str);
	if (!tmp)
		return (tmp);
	ret = treat_var(tmp);
	return (ret);
}

static char	*do_cd_next(t_data *data, char **args, char *path)
{
	char	*str;

	if (args[1][0] == '/')
			data->cd.ret = chdir(args[1]);
	else
	{
		if (args[1][0] == '~')
			str = if_tilde(data, args[1]);
		else if (args[1][0] == '-' && args[1][1] == '\0')
			str = get_env_val(data, "OLDPWD");
		else
		{
			str = malloc(ft_strlen(path) + ft_strlen(args[1]) + 2);
			//if (!str)
				//erreur
			str = cd_join(path, args[1], str);
		}
		if (!str)
			data->cd.ret = 1;
		else
			data->cd.ret = chdir(str);
	}
	return (str);
}

static void	do_cd(t_data *data, char **args, int len)
{
	char	path[PATH_MAX];
	char	*pwd;
	char	*str;

	getcwd(path, PATH_MAX);
	pwd = get_env_val(data, "PWD");
	if (len == 1)
	{
		str = if_tilde(data, args[0]);
		data->cd.ret = chdir(str);
	}
	else
		str = do_cd_next(data, args, path);
	if (data->cd.ret != 0 && !(args[1][0] == '-' && args[1][1] == '\0'))
		cd_error(data, args[1]);
	else if (data->cd.ret != 0)
		cd_error(data, str);
	else
	{
		getcwd(path, PATH_MAX);
		change_pwd_vars(data, pwd, path);
		data->last_ret = 0;
	}
}

void	main_cd(t_data *data, char **args)
{
	int		len;
	char	*new_dir;

	len = 0;
	data->last_ret = 0;
	while (args[len])
		len++;
	if (len > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->last_ret = 1;
	}
	else
		do_cd(data, args, len);
}