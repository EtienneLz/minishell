#include "../../includes/minishell.h"

int	check_pipe(t_token	*actual)
{
	while (actual && actual->type == STRING || actual->type == STRING_SIMPLE)
	{
		if (actual->next->type == PIPE)
			return (1);
		actual = actual->next;
	}
	return (0);
}

t_token	*to_next_command(t_token *actual)
{
	while (actual && actual != COMMAND)
		actual = actual->next;
	return (actual);
}