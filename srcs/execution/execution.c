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

static int	child(t_data *data)
{
	char	*bin;
	g_pid = fork();
	if (g_pid == 0)
	{
		if (!check_built_in(data, data->splitted_args[data->command_nb][0]))
		{
			bin = get_bin_path(data->splitted_args[data->command_nb][0]);
			if (bin == NULL)
				bin = data->splitted_args[data->command_nb][0];
			if (execve(bin, data->splitted_args[data->command_nb], NULL) == -1)
			{
				if (errno == 2)
					printf("minishell: command not found: %s\n", data->splitted_args[data->command_nb][0]);
				else
					perror("minishell");
				exit(0);
			}
		}
		exit(0);
	}
	else
		return (0);
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

static int	exe_pipe(t_data *data, int *fdin, int *fdout)
{
	int		fd[2];
	char	*bin;

	if (data->command_nb == data->nb_pipe)
	{
		if (data->nb_outfiles)
			*fdout = outfile_func(data, fdout);
		else
		{
			*fdout = dup(data->tmpout);
		}
	}
	else
	{
		if (pipe(fd))
			return (-1);
		*fdin = fd[0];
		*fdout = fd[1];
	}
	dup2(*fdout, STDOUT);
	close(*fdout);
	child(data);
	data->command_nb++;
	data->actual = to_next_command(data->actual);
	return (0);
}

int	execution(t_data *data)
{
	char	*bin;
	int		fdin;
	int		fdout;
	int		nb_next_cmd;

	data->tmpin = dup(STDIN);
	data->tmpout = dup(STDOUT);
	if (data->nb_infiles > 0)
		fdin = open(data->infile[0], O_RDONLY);
	else
		fdin = dup(data->tmpin);
	data->actual = data->first;
	//data->splitted_args = split_arg(data);
	while (data->actual)
	{
		if (data->actual->type == COMMAND)
		{
			nb_next_cmd = nb_next_cmd(actual);
			while (data->actual->type == COMMAND && nb_next_cmd)
			{
				dup2(fdin, STDIN);
				close(fdin);
				exe_pipe(data, &fdin, &fdout);
				nb_next_cmd--;
			}
			dup2(data->tmpin, STDIN);
			dup2(data->tmpout, STDOUT);
			close(data->tmpin);
			close(data->tmpout);
			waitpid(g_pid, NULL, 0);
		}
		if (data->actual)
			data->actual = data->actual->next;
	}
	return (0);
}