#include "../../../includes/minishell.h"

void    unset_error(t_data *data, char *str)
{
    ft_putstr_fd("minishell: unset: `", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
    data->last_ret = 1;
}

int		cmp_unset_arg(t_data *data, char *str)
{
	int i;

	i = 0;
	while (data->envp[i])
	{
		if (if_equal(data, data->envp[i], str) == 1)
			return (1);
		i++;
	}
	return (0);
}

void    get_unset_valid_args(t_data *data, char *str, int *i)
{
    int len;

    len = ft_strlen(str);
    data->unset.args[*i] = malloc((len + 1) * sizeof(char));
    //if (!(data->export.args[*i]))
        //message erreur + sortie
    ft_strcpy(data->unset.args[*i], str);
    data->unset.valid_args--;
    (*i)++;
    if (data->unset.valid_args == 0)
        data->unset.args[*i] = NULL;
}

void    check_unset_args(t_data *data, char **args)
{
    int i;
    int j;
    int k;

    i = 1;
    k = 0;
    while (args[i])
    {
        j = 0;
        while (args[i] && ((!(ft_isalpha(args[i][j])) && args[i][j] != '_') || (args[i][0] == '_' && args[i][1] == '=')))
        {
            if (data->unset.check == 0 && args[i][0] != '_')
                unset_error(data, args[i]);
            i++; //ajouter message d'erreur
        }
        while (args[i] && args[i][j] && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
            j++;
        if (args[i] && !args[i][j] && cmp_unset_arg(data, args[i]) == 1)
        {
            if (data->unset.check != 0 && data->unset.valid_args != 0)
                get_unset_valid_args(data, args[i], &k);
            else
                data->unset.valid_args++;
			i++;
        }
		else if (args[i])
			i++;
    }
    data->unset.check = 1;
}


void	unset_main_check(t_data *data, char **args)
{
	check_unset_args(data, args);
	if (data->unset.valid_args != 0)
	{
		data->unset.args = malloc((data->unset.valid_args + 1) * sizeof(char *));
        //if (!tmp)
            //message erreur + sortie
        check_unset_args(data, args);
	}
	data->unset.check = 0;
}