/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:18:52 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/23 13:18:59 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_built_in(t_data *data)
{
	char 	*command;
	int		ret;

	ret = 1;
	command = data->first->content;
	/*if (ft_strcmp(command, "cd"))
		cd(data);
	else if (ft_strcmp(command, "echo"))
	{
		if (data->first->next->type == OPTION)
			echo(data, 1);
		else
			echo(data, 0);
	}
	else if (ft_strcmp(command, "env"))
		env(data);
	else */if (!ft_strcmp(command, "exit"))
		ft_exit(data);
	/*else if (ft_strcmp(command, "pwd"))
		pwd();
	else if (ft_strcmp(command, "unset"))
		unset(data);
	else if (ft_strcmp(command, "export"))
		export(data);*/
	else
		ret = 0;
	return (ret);
}

static char	*get_bin_path(char *command)
{
	char	*path;
	char	**path_split;
	char	*bin;
	int		i;

	path_split = NULL;
	bin = NULL;
	path = ft_strdup(getenv("PATH"));
	i = 0;

	if (!path)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (command[0] != '/' && ft_strncmp(command, "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		while (path_split[i])
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + ft_strlen(command) + 2));
			if (bin == NULL)
				break ;
			ft_strlcat(bin, path_split[i], ft_strlen(bin) + ft_strlen(path_split[i]) + 2);
			ft_strlcat(bin, "/", ft_strlen(bin) + 2);
			ft_strlcat(bin, command, ft_strlen(bin) + ft_strlen(command) + 2);
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
			i++;
		}
		free_tab(path_split);
		return (bin);
	}
	else
	{
		free(path);
		path = NULL;
		return (NULL);
	}
}

static int	exe_pipe(t_data *data)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		//ft_close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		data->pipe.pipe_in = pipefd[0];
		data->pipe.pid = -1;
		data->pipe.parent = 0;
		return (2);
	}
	else
	{
		//ft_close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		data->pipe.pipe_out = pipefd[1];
		data->pipe.pid = pid;
		return (1);
	}
}

static void	execution_ve(t_data *data, char *bin)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(bin, data->splitted_args[0], NULL) == -1)
		{
			if (errno == 14)
				printf("minishell: command not found: %s\n", data->splitted_args[0][0]);
			else
				perror("minishell");
		}
		exit(EXIT_SUCCESS);
	}
}

int	execution(t_data *data)
{
	t_token	*actual;
	int		command_nb;
	char	*bin;

	command_nb = 0;
	actual = data->first;
	data->splitted_args = split_arg(data);
	while (actual)
	{
		if (actual->type == COMMAND)
		{
			if (check_pipe(actual))
			{

			}
			else
			{
				bin = get_bin_path(data->first->content);
				if (bin == NULL && actual->content[0] == '.' && actual->content[1] == '/')
					bin = data->first->content;
				execution_ve(data, bin);
			}
		}
		actual = actual->next;
	}


	
	if (check_built_in(data))
		return (0);
	else
	{
		
		if (data->nb_pipe > 0)
		{
			bin = get_bin_path(data->first->content);
				if (bin == NULL && data->first->content[0] == '.' && data->first->content[1] == '/')
			bin = data->first->content;
		}
		execution_ve(data, bin);
	}
	return (0);
}