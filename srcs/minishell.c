/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 20:05:30 by mseligna         ###   ########.fr       */
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
	char	*arg[3];
	//int i = 0;

	data.envp = envp;
	init(&data);
	arg[0] = "export";
	arg[1] = "ZSH=hello";
	arg[2] = NULL;
	//main_check(&data, arg);
	export_args(&data, arg);
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
