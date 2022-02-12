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

static char *treat_var(t_data *data, char *var)
{
    int     i;
    int     size;
    char    *ret;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    size = ft_strlen(var) - i;
    ret = malloc(sizeof(char) * size);
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

static char *check_exist(t_data *data, char *var)
{
    int     i;
    char    *ret;

    i = 0;
    ret = NULL;
    while (data->envp[i])
    {
        if (!ft_strncmp(var, data->envp[i], ft_strlen(var)))
        {
            ret = malloc(sizeof(char) * (ft_strlen(data->envp[i]) + 1));
            ft_strcpy(ret, data->envp[i]);
    	    return (ret);
        }
        i++;
    }
    return (NULL);
}

static char  *size_var(t_data *data, char *var)
{
    char    *var_name;
    char    *convert_var;
    int     i;

    i = 0;
    var_name = malloc(sizeof(char) * (ft_strlen(var) + 2));
    while (var[i + 1] && var[i + 1] != ' ')
    {
        var_name[i] = var[i + 1];
        i++;
    }
    var_name[i] = '=';
    var_name[i + 1] = '\0';
    convert_var = check_exist(data, var_name);
    if (!convert_var)
    {
        convert_var = malloc(sizeof(char));
        convert_var = "";
        return (convert_var);
    }
    return (treat_var(data, convert_var));
} 

static char *unsplit(char **split_str)
{
    int     i;
    int     j;
    int     size;
    char    *str;

    i = 1;
    str = ft_strdup(split_str[0]);
    while (split_str[i])
    {
        str = ft_strjoin_free(str, split_str[i]);
        i++;
    }
    /*size = 0;
    while (split_str[i])
    {
        size += ft_strlen(split_str[i]);
        i++;
    }
    if (split_str[0][0] == '\"')
        size -= 2;
    str = malloc(sizeof(char) * size + 1);
    size = 0;
    i = 0;
    while (split_str[i])
    {
        j = 0;
        while (split_str[i][j])
        {
            str[size] = split_str[i][j];
            size++;
            j++;
        }
        i++;
    }*/
    //printf("%s\n", str);
    return (str);
}

static void check_var(t_data *data, char *str, t_token *actual)
{
    char    **split_str;
    char    *replaced;
    int     i;
    int     j;

    i = 0;
    split_str = ft_split_noskip(str, '$');
    while (split_str[i])
    {
        if (split_str[i][0] == '$')
        {
            replaced = size_var(data, split_str[i]);
            free(split_str[i]);
            split_str[i] = replaced;
        }
        i++;
    }
    free (actual->content);
    actual->content = unsplit(split_str);
}

void expand(t_data *data)
{
    t_token *actual;

    actual = data->first;
    while (actual)
    {
        if (actual->type == STRING)
        {
            if (actual->content[0] == '\"')
                actual->content = check_quotes(actual->content);
            check_var(data, actual->content, actual);
        }
        else if (actual->type == STRING_SIMPLE)
            if (actual->content[0] == '\'')
                actual->content = check_quotes(actual->content);
        actual = actual->next;
    }
}