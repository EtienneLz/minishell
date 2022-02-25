#include "../../includes/minishell.h"

int	get_quoted(char *command, int i, char quote)
{
	int	len;

	len = 1;
	i++;
	while (command[i])
	{
		if (command[i] == quote && (command[i + 1] == ' '
				|| command[i + 1] == '|' || command[i + 1] == '<'
				|| command[i + 1] == '>'))
			break ;
		len++;
		i++;
	}
	return (len + 1);
}
