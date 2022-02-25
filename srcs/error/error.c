#include "../../includes/minishell.h"

void	print_error(char *error_str)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(error_str, STDERR);
}
