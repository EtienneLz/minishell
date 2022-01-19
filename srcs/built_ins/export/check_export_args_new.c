#include "../../../includes/minishell.h"

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
        while ((args[i] && !(ft_isalpha(args[i][j])) && args[i][j] != '_') || (args[i][0] == '_' && args[i][1] == '='))
            i++; //ajouter message d'erreur
		while (args[i] && cmp_arg(data, args[i]) == 1)
			i++;
        while (args[i] && args[i][j] && args[i][j] != '=' && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
            j++;
        if (args[i] && args[i][j] && args[i][j] != '=')
            i++; //ajouter message d'erreur
        else if (args[i] && (!args[i][j] || args[i][j] == '='))
        {
            if (data->export.check != 0 && data->export.valid_args != 0)
                get_valid_args(data, args[i], &k);
            else
                data->export.valid_args++;
            i++;
        }
    }
    data->export.check = 1;
}

void    main_check(t_data *data, char **args)
{
    int i = 1;
	while (args[i])
		cmp_arg(data, args[i++]);
	data->export.equal = 1;
    check_export_args(data, args);
    data->export.args = malloc((data->export.valid_args + 1) * sizeof(char *));
    //if (!tmp)
        //message erreur + sortie
    check_export_args(data, args);
    data->export.check = 0;
}