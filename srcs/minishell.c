/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:23 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/24 23:36:55 by mseligna         ###   ########.fr       */
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
	char 	*cd[2];
	//int i = 0;
	//int ret;

	init(&data);
	data.envp = envp;
	data.cd.home = getenv("HOME");
	arg[0] = "unset";
	arg[1] = "PWD";
	//arg[2] = "co(uco";
	//arg[3] = "SHLVL";
	//arg[4] = "9SLVL";
	//arg[5] = "ZSH";
	arg[2] = NULL;
	cd[0] = "cd";
	cd[1] = NULL;
	main_unset(&data, arg);
	main_cd(&data, cd);
	//export_no_arg(&data);
	//printf("%s\n", getenv("PWD"));
	//while (data.envp[i])
	//	printf("%s\n", data.envp[i++]);
	export_no_arg(&data);
	//main_cd(&data, cd);
	//printf("ret = %d\n", data.cd.ret);
	//export_no_arg(&data);
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
