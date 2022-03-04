/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:56:29 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/08 09:56:29 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*treat_var(char *var)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	size = ft_strlen(var) - i;
	ret = mallocer(&ret, sizeof(char) * size);
	size = 0;
	i++;
	while (var[i])
	{
		ret[size] = var[i];
		i++;
		size++;
	}
	ret[size] = '\0';
	free(var);
	return (ret);
}

char	*check_exist(t_data *data, char *var)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (data->envp[i])
	{
		if (!ft_strncmp(var, data->envp[i], ft_strlen(var)))
		{
			ret = mallocer(&ret, sizeof(char) * (ft_strlen(data->envp[i]) + 1));
			ft_strcpy(ret, data->envp[i]);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

static char	*size_var(t_data *data, char *var)
{
	char	*var_name;
	char	*convert_var;
	int		i;

	i = 0;
	var_name = mallocer(&var_name, sizeof(char) * (ft_strlen(var) + 2));
	while (var[i + 1] && var[i + 1] != ' ')
	{
		var_name[i] = var[i + 1];
		i++;
	}
	var_name[i] = '=';
	var_name[i + 1] = '\0';
	convert_var = check_exist(data, var_name);
	if (var_name)
		free(var_name);
	if (!convert_var)
	{
		convert_var = NULL;
		return (convert_var);
	}
	return (treat_var(convert_var));
}

static char	*unsplit(char **split_str)
{
	int		i;
	char	*str;

	i = 1;
	if (split_str[0] == NULL)
		return (NULL);
	str = ft_strdup(split_str[0]);
	while (split_str[i])
	{
		str = ft_strjoin_free(str, split_str[i]);
		i++;
	}
	return (str);
}

void	check_var(t_data *data, char *str, t_token *actual)
{
	char	**split_str;
	char	*replaced;
	int		i;

	i = 0;
	split_str = ft_split_noskip(str, '$');
	while (split_str[i])
	{
		if (split_str[i][0] == '$')
		{
			if (split_str[i][1] == '?')
				replaced = ft_itoa(data->ret);
			else
				replaced = size_var(data, split_str[i]);
			free(split_str[i]);
			split_str[i] = replaced;
		}
		i++;
	}
	free (actual->content);
	actual->content = unsplit(split_str);
	if (split_str)
	{
		free_tab(split_str);
		free(split_str);
	}
}
