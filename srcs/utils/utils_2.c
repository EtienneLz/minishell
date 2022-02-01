#include "../../includes/minishell.h"

int	check_pipe(t_token	*actual)
{
	if (actual->next)
		actual = actual->next;
	else
		return (0);
	while (actual && actual->type == STRING || actual->type == STRING_SIMPLE || actual->type == OPTION)
	{
		if (actual->next == NULL)
			return (0);
		if (actual->next->type == PIPE)
			return (1);
		actual = actual->next;
	}
	return (0);
}

t_token	*to_next_command(t_token *actual)
{
	t_token	*act;

	act = actual;
	if (act->next == NULL)
		return (NULL);
	act = act->next;
	while (act && act->type != COMMAND)
	{
		act = act->next;
	}
	return (act);
}