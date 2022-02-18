#include "../../../includes/minishell.h"

void	export_error(t_data *data, char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	data->last_ret = 1;
}