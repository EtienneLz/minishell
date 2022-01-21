/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/21 19:03:25 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	reset_var(t_data *data)
{
	ft_lstfree(data);
	splitted_args_free(data->splitted_args);
}

static void	mini_routine(t_data *data, char *buffer)
{
	if (split_command(data, buffer))
		return ;
	if (tokenizer(data))
		return ;
	if (execution(data))
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*arg[3];
	int i = 0;
	int ret;

	init(&data);
	data.envp = envp;
	arg[0] = "cd";
	arg[1] = "..";
	//arg[2] = "co(uco";
	//arg[3] = "SHLVL";
	//arg[4] = "9SLVL";
	//arg[5] = "ZSH";
	arg[2] = NULL;
	main_cd(&data, arg);
	printf("ret = %d\n", data.cd.ret);
	pwd();
//	while (data.envp[i])
//		printf("%s\n", data.envp[i++]);
	//main_unset(&data, arg);
	//export_no_arg(&data);
	//main_check(&data, arg);
	//export_args(&data, arg);
	//export_no_arg(&data);
	/*(void)argc;
	(void)argv;
	(void)envp;
	while (data.buffer)
	{
		data.buffer = readline("$> ");
		mini_routine(&data, data.buffer);
		reset_var(&data);
	}*/
	return (0);
}
