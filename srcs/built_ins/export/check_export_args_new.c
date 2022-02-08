#include "../../../includes/minishell.h"

void    export_error(t_data *data, char *str)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(str, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
    data->last_ret = 1;
}

void    get_valid_args(t_data *data, char *str, int *i)
{
    int len;

    len = ft_strlen(str);
    data->export.args[*i] = malloc((len + 1) * sizeof(char));
    //if (!(data->export.args[*i]))
        //message erreur + sortie
    ft_strcpy(data->export.args[*i], str);
    data->export.valid_args--;
    (*i)++;
    if (data->export.valid_args == 0)
        data->export.args[*i] = NULL;
}

void    check_export_args(t_data *data, char **args)
{
    int i;
    int j;
    int k;

    i = 1;
    k = 0;
    while (args[i])
    {
        j = 0;
        if (args[i] && ((!(ft_isalpha(args[i][j])) && args[i][j] != '_') || (args[i][0] == '_' && args[i][1] == '=')))
        {
            if (data->export.check == 0 && args[i][0] != '_')
                export_error(data, args[i]);
            i++;
        }
		else if (args[i] && cmp_export_arg(data, args[i]) == 1)
			i++;
        else
        {
            while (args[i] && args[i][j] && args[i][j] != '=' && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
              j++;
            if (args[i] && (!args[i][j] || args[i][j] == '='))
            {
                if (data->export.check != 0 && data->export.valid_args != 0)
                    get_valid_args(data, args[i], &k);
                else
                    data->export.valid_args++;
            }
            else if (args[i])
                if (data->export.check == 0)
                    printf("minishell: export: `%s': not a valid identifier\n", args[i]);
            i++;
        }
    }
    data->export.check = 1;
}

void    export_main_check(t_data *data, char **args)
{
    int i = 1;
	while (args[i])
		cmp_export_arg(data, args[i++]);
	data->export.equal = 1;
    check_export_args(data, args);
    if (data->export.valid_args > 0)
    {
        data->export.args = malloc((data->export.valid_args + 1) * sizeof(char *));
        //if (!tmp)
            //message erreur + sortie
        check_export_args(data, args);
    }
    data->export.check = 0;
}