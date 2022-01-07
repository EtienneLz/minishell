/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/07 19:56:26 by mseligna         ###   ########.fr       */
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
	char	*arg[4];
	//int i = 0;

	data.envp = envp;
	init(&data);
	arg[0] = "_sa;lut=hi";
	arg[1] = "ziBou=m.e";
	arg[2] = "Bi5p=paf";
	arg[3] = NULL;
	main_check(&data, arg);
	export_args(&data, data.export.args);
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
