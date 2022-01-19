#include "../../../includes/minishell.h"

char	*join_arg(char *s1, char *s2)
{
	char	*dest;
	int		n;
	int		m;
	int		i;
	int		j;

	i = 0;
	j = 0;
	n = 0;
	m = 0;
	while (s1[n] != '=')
		n++;
	while (s2[m] != '=')
		m++;
	dest = malloc((n + (ft_strlen(s2) - m) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < n)
		dest[j++] = s1[i++];
	while (s2[m])
		dest[j++] = s2[m++];
	dest[j] = '\0';
	return (dest);
}

int		if_equal(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '=')
		i++;
	while (s2[j] && s2[j] != '=')
		j++;
	if (i == j)
	{
		if (ft_strncmp(s1, s2, i) != 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

int		cmp_arg(t_data *data, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	//printf("%s\n", str);
	while (data->envp[i])
	{
		//printf("i = %d\n", i);
		if (if_equal(data->envp[i], str) == 1)
		{
			if (data->export.equal != 1)
			{
				while (str[j])
				{
					if (str[j] == '=')
					{
						data->envp[i] = join_arg(data->envp[i], str);
						//printf("%s\n", data->envp[i]);
						break ;
					}
					j++;
				}
			}
			//printf("i doublon = %d\n", i);
			return (1);
		}
		i++;
	}
	return (0);
}
