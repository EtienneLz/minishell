#include "../../../includes/minishell.h"

int		if_equal(t_data *data, char *s1, char *s2)
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
		{
			if (s2[j] == '=' && data->export.check == 0)
				data->export.equal++;
			return (1);
		}
	}
	return (0);
}

int		cmp_arg(t_data *data, char *str)
{
	int i;
	int j;
	//int	check;

	i = 0;
	j = 0;
	//check = data->export.equal;
	//printf("check = %d\n", check);
	while (data->envp[i])
	{
		if (if_equal(data, data->envp[i], str) == 1)
		{
			while (str[j])
			{
				if (str[j] == '=')
				{
					data->envp_i = i;
					return (2);
				}
				j++;
			}
			return (1);
			/*if (check == data->export.equal)
				return (1);
			else
			{
				printf("equal = %d\n", data->export.equal);
				//data->export.equal = check;
				data->envp_i = i;
				return (2);
			}*/
		}
		i++;
	}
	return (0);
}

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

void 	copy_equal(t_data *data)
{
	int	i;

	i = 0;
	while (data->export.args[i])
	{
		if (cmp_arg(data, data->export.args[i]) == 2)
		{
			data->envp[data->envp_i] = join_arg(data->envp[data->envp_i], data->export.args[i]);
			data->envp_i = 0;
		}
		i++;
	}
	data->export.equal = 0;
}

char	**copy_args(t_data *data, char **str, char **dest, int *i)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	while (str[len])
		len++;
	while (j < len)
	{
		if (cmp_arg(data, str[j]) != 2)
		{
			dest[*i] = malloc((ft_strlen(str[j]) + 1) * sizeof(char));
			//if (!dest[*i])
			//	return (NULL);
			ft_strcpy(dest[*i], str[j]);
			(*i)++;
		}
		j++;
	}
	data->export.equal = 0;
	return (dest);
}