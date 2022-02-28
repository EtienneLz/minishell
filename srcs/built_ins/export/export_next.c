#include "../../../includes/minishell.h"

int	skip_env(char **tab, int i)
{
	if (tab[i][0] == '_' && tab[i][1] == '=')
		i++;
	return (i);
}

char	**copy_env(char **tab, char **dest, int *i)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (tab[len])
		len++;
	while (j < len)
	{
		dest[*i] = malloc((ft_strlen(tab[j]) + 1) * sizeof(char));
		if (!dest[*i])
		{
			free_tab(dest);
			return (NULL);
		}
		ft_strcpy(dest[*i], tab[j]);
		(*i)++;
		j++;
	}
	return (dest);
}

char	**sort_env_atoz(char **tab, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}
