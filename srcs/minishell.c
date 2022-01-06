/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/06 18:02:11 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	ft_lstfree(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*buffer;
	char *args[4]; //= {salut=hi,bibou=me,bip=paf};
	//int i = 0;

	data.envp = envp;
	args[0] = "salut=hi";
	args[1] = "zibou=me";
	args[2] = "Bip=paf";
	args[3] = NULL;
	//while (args[i])
	//	i++;
	//printf("len args = %d\n", i);
	export_args(&data, args);
	export_no_arg(&data);
	/*buffer = "";
	(void)argc;
	(void)argv;
	(void)envp;
	while (buffer)
	{
		buffer = readline("$> ");
		split_command(&data, buffer);
		reset_var(&data);
	}
	//free(buffer);
	write(STDOUT, "So you have chosen death\n", 25);*/
	return (0);
}
