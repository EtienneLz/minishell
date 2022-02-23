#include "../../includes/minishell.h"

void	print_error(t_data *data, char *error_str)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(error_str, STDERR);
}