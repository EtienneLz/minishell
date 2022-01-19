#include "../../../includes/minishell.h"

void    get_valid_args(t_data *data, char *str, int *i)
{
    int len;

    len = ft_strlen(str);
	//printf("len = %d\n", len);
	//printf("%s\n", str);
	//printf("valid = %d\n", data->export.valid_args);
	//printf("i = %d\n", *i);
    data->export.args[*i] = malloc((len + 1) * sizeof(char));
    //if (!(data->export.args[*i]))
        //message erreur + sortie
    ft_strcpy(data->export.args[*i], str);
    data->export.valid_args--;
    (*i)++;
	printf("ok second\n");
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
	printf("check first 2= %d\n", data->export.check);
    while (args[i])
    {
        j = 0;
		//printf("valid = %d\n", data->export.valid_args);
		//printf("%s\n", args[i]);
        while ((args[i] && !(ft_isalpha(args[i][j])) && args[i][j] != '_') || (args[i][0] == '_' && args[i][1] == '='))
            i++; //ajouter message d'erreur
		while (args[i] && cmp_arg(data, args[i]) == 1)
		{
			//printf("%s\n", args[i]);
			i++;
		}
		//printf("%s\n", args[i]);
        while (args[i] && args[i][j] && args[i][j] != '=' && (ft_isalnum(args[i][j]) || args[i][j] == '_'))
            j++;
        if (args[i] && args[i][j] && args[i][j] != '=')
            i++; //ajouter message d'erreur
        else if (args[i] && (!args[i][j] || args[i][j] == '='))
        {
            if (data->export.check != 0 && data->export.valid_args != 0)
                get_valid_args(data, args[i], &k);
            else
			{
				printf("ok first\n");
                data->export.valid_args++;
			}
            i++;
        }
    }
    data->export.check = 1;
}

void    main_check(t_data *data, char **args)
{
    int i = 1;
	//printf("ok\n");
	while (args[i])
	{
		//printf("i = %d\n", i);
		cmp_arg(data, args[i]);
		i++;
	}
	printf("valid first = %d\n", data->export.valid_args);
	printf("check first = %d\n", data->export.check);
	data->export.equal = 1;
	//printf("valid = %d\n", data->export.valid_args);
    check_export_args(data, args);
	printf("valid second = %d\n", data->export.valid_args);
	//printf("valid = %d\n", data->export.valid_args);
    data->export.args = malloc((data->export.valid_args + 1) * sizeof(char *));
    //if (!tmp)
        //message erreur + sortie
    check_export_args(data, args);
    data->export.check = 0;
}