#include "../../../includes/minishell.h"

void	cd_error(t_data *data, char *str)
{
	if (!str)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	data->last_ret = 1;
}
