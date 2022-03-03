#include "../../../includes/minishell.h"

void	unset_error(t_data *data, char *str)
{
	if (data->last_ret != 1000)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	data->last_ret = 1;
}
