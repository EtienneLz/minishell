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

static int	check_built_in(t_data *data, char *command)
{
	int		ret;

	ret = 1;
	if (!ft_strcmp(command, "cd"))
		main_cd(data, data->splitted_args[data->command_nb]);
	/*else if (!ft_strcmp(command, "echo"))
	{
		if (data->first->next->type == OPTION)
			echo(data, 1);
		else
			echo(data, 0);
	}*/
	else if (!ft_strcmp(command, "env"))
		ft_env(data, data->splitted_args[data->command_nb]);
	else if (!ft_strcmp(command, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(command, "unset"))
		main_unset(data, data->splitted_args[data->command_nb]);
	else if (!ft_strcmp(command, "export"))
		main_export(data, data->splitted_args[data->command_nb]);
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

static int	outfile_func(t_data *data, int *fdout)
{
	int	i;
	int	fd;

	i = 0;
	while (i < data->nb_outfiles - 1)
	{
		fd = open(data->outfile[i], O_CREAT | O_RDWR |
			O_APPEND, 0644);
		if (fd == -1)
			perror("fd");
		else
			close(fd);
		i++;
	}
	if (data->last_out == 1)
		fd = open(data->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(data->outfile[i], O_CREAT | O_RDWR | O_APPEND, 0644);
	return (fd);
}

static void	redirection(t_token *actual)
{
	int	fd;

	if (actual->prev_out)
		fd = open(actual->prev_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (actual->prev_d_out)
		fd = open(actual->prev_d_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (actual->prev_out || actual->prev_d_out)
	{
		dup2(fd, STDOUT);
		dup2(fd, STDERR);
	}
	if (fd)
		close(fd);
}

static void	redirection2(t_token *actual)
{
	int	fd;

	if (actual->next_out)
		fd = open(actual->next_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (actual->next_d_out)
		fd = open(actual->next_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (actual->next_out || actual->next_d_out)
	{
		dup2(fd, STDOUT);
		dup2(fd, STDERR);
	}
	if (fd)
		close (fd);
}

static int	child(t_data *data, t_token *actual)
{
	char	*bin;

	if (actual->prev_in || actual->prev_out || actual->prev_d_out)
		redirection(actual);
	if (actual->prev_pipe)
	{
		dup2(data->pipes[0], STDIN);
		close(data->pipes[0]);
	}
	if (actual->next_pipe)
	{
		dup2(data->pipes[1], STDOUT);
		close (data->pipes[1]);
	}
	else if (actual->next_out || actual->next_d_out)
		redirection2(actual);
	else
	{
		dup2(data->tmpout, STDOUT);
	}
	bin = get_bin_path(actual->args[0]);
	if (bin == NULL)
		bin = actual->args[0];
	if (check_built_in(data, actual->args[0]) == 0)
	{
		if (execve(bin, actual->args, NULL) == -1)
		{
			if (errno == 2)
				printf("minishell: command not found: %s\n", actual->args[0]);
			else
				perror("minishell");
		}
	}
	printf("ALLOW?\n");
	exit(0);
}





static int	parent(t_data *data, t_token *actual)
{
	int	i;
	int	ex;
	int	ret;
	int	status;

	ret = 0;
	i = 0;
	ex = 0;
	status = 0;
	if (actual->id == data->nb_command - 1)
	{
		//dup2(data->pipes[1], 0);
		//close(data->pipes[0]);
		while (i < data->nb_command)
		{
			printf("here %d\n", i);
			waitpid(data->pid[i], &status, 0);
			if (i == data->nb_command - 1)
			{
				ex = WIFEXITED(status);
				if (ex > -1)
					ret = WEXITSTATUS(status);
			}
			i++;
		}
	}
	return (ret);
}

static int	exe_pipe(t_data *data, t_token *actual, int i)
{
	char	*bin;
	int		error;

	error = 0;
	printf("%d\n", actual->next_pipe);
	if (actual->next_pipe)
		error = pipe(data->pipes);
	if (error != 0)
		return (1);
	data->pid[i] = fork();
	if (data->pid[i] == 0)
		child(data, actual);
	else
		parent(data, actual);
	return (0);
}

int	execution(t_data *data)
{
	char	*bin;
	int		fdin;
	int		fdout;

	data->tmpin = dup(STDIN);
	data->tmpout = dup(STDOUT);
	fdin = dup(data->tmpin);
	data->actual = data->first;
	if (data->actual->type != COMMAND)
		data->actual = to_next_command(data->actual);
	while (data->command_nb < data->nb_command)
	{
		exe_pipe(data, data->actual, data->command_nb);
		data->command_nb++;
		data->actual = to_next_command(data->actual);
		if (!data->actual)
			break;
	}
	dup2(data->tmpin, STDIN);
	dup2(data->tmpout, STDOUT);
	close(data->tmpin);
	close(data->tmpout);
	free(data->pid);
	return (0);
}