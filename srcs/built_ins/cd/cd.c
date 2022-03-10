/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:21:52 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:21:52 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_env_val(t_data *data, char *str)
{
	char	*ret;
	char	*tmp;

	tmp = check_exist(data, str);
	if (!tmp)
		return (tmp);
	ret = treat_var(tmp);
	return (ret);
}

static char	*only_one(t_data *data, char *s)
{
	char	*str;

	str = if_tilde(data, s);
	data->cd.ret = chdir(str);
	return (NULL);
}

static char	*do_cd_next(t_data *data, char **args, char *path)
{
	char	*str;

	str = NULL;
	if (args[1][0] == '/' && args[1][1] == '\0')
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
			if (!str)
				alloc_error(data, "cd");
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
		str = only_one(data, args[0]);
	else
		str = do_cd_next(data, args, path);
	if (data->cd.ret != 0 && ((!(args[1][0] == '-') || !(args[1][0] == '~'))
		&& args[1][1] == '\0'))
		cd_error(data, args[1]);
	else if (data->cd.ret != 0)
		cd_error(data, str);
	else
	{
		getcwd(path, PATH_MAX);
		change_pwd_vars(data, pwd, path);
		data->last_ret = 0;
	}
	free(pwd);
	if (str && !(args[1][0] == '~' && args[1][1] == '\0'))
		free(str);
}

int	main_cd(t_data *data, char **args)
{
	int		len;

	len = 0;
	while (args[len])
		len++;
	if (len > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		data->last_ret = 1;
	}
	else
		do_cd(data, args, len);
	if (data->last_ret == 1000)
		return (0);
	else
		return (data->last_ret);
}
