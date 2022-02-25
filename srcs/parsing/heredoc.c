#include "../../includes/minishell.h"

char	**get_sep(t_data *data)
{
	char	**sep;
	int		i;
	t_token	*actual;

	actual = data->first;
	sep = malloc(sizeof(char *) * (ft_atoi(data->outfile) + 1));
	if (!sep)
		alloc_error(data, NULL);
	i = 0;
	while (actual)
	{
		if (actual->type == LL_ARROW && actual->next)
		{
			ft_strcpy(sep[i], actual->next->content);
			i++;
		}
		actual = actual->next;
	}
	sep[i] = NULL;
	return (sep);
}

void	ft_heredoc(t_data *data)
{
	char	**sep;

	sep = get_sep(data);
}
