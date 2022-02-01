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

static int	child(t_data *data)
{
	char	*bin;
	data->pid = fork();
	if (data->pid == 0)
	{
		bin = get_bin_path(data->splitted_args[data->command_nb][0]);
		if (bin == NULL)
			bin = data->splitted_args[data->command_nb][0];
		if (execve(bin, data->splitted_args[data->command_nb], NULL) == -1)
		{
			if (errno == 14)
				printf("minishell: command not found: %s\n", data->splitted_args[data->command_nb][0]);
			else
				perror("minishell");
			return (1);
		}
	}
	else
		return (0);
}

static int	exe_pipe(t_data *data, int *fdin, int *fdout)
{
	int		fd[2];
	char	*bin;

	if (data->command_nb == data->nb_pipe)
		*fdout = dup(data->tmpout);
	else
	{
		if (pipe(fd))
			return (-1);
		*fdin = fd[0];
		*fdout = fd[1];
	}
	dup2(*fdout, STDOUT);
	close(*fdout);
		/*if (!data->splitted_args[data->command_nb])
			break ;*/
	child(data);
	data->command_nb++;
	data->actual = to_next_command(data->actual);
	
	return (0);
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
		if (execve(bin, data->splitted_args[data->command_nb], NULL) == -1)
		{
			if (errno == 14)
				printf("minishell: command not found: %s\n", data->splitted_args[data->command_nb][0]);
			else
				perror("minishell");
		}
		exit(EXIT_SUCCESS);
	}
}

int	execution(t_data *data)
{
	char	*bin;
	int		fdin;
	int		fdout;

	data->tmpin = dup(STDIN);
	data->tmpout = dup (STDOUT);
	fdin = dup(data->tmpin);
	data->actual = data->first;
	data->splitted_args = split_arg(data);
	while (data->actual)
	{
		if (data->actual->type == COMMAND)
		{
			if (check_pipe(data->actual))
			{
				while (data->command_nb < data->nb_pipe + 1)
				{
					dup2(fdin, STDIN);
					close(fdin);
					exe_pipe(data, &fdin, &fdout);
				}
				dup2(data->tmpin, STDIN);
				dup2(data->tmpout, STDOUT);
				close(data->tmpin);
				close(data->tmpout);
				wait(&data->pid);
			}
			else
			{
				if (check_built_in(data))
					break ;
				bin = get_bin_path(data->actual->content);
				if (bin == NULL)
					bin = data->actual->content;
				execution_ve(data, bin);
			}
			data->command_nb++;
		}
		if (data->actual)
			data->actual = data->actual->next;
	}
	return (0);
}