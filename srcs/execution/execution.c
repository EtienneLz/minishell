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

static int	check_built_in(t_data *data, char **args)
{
	int		ret;

	ret = 1;
	/*int i = 0;
	while(args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}*/
	if (!ft_strcmp(args[0], "cd"))
		main_cd(data, args);
	/*else if (!ft_strcmp(command, "echo"))
	{
		if (data->first->next->type == OPTION)
			echo(data, 1);
		else
			echo(data, 0);
	}*/
	else if (!ft_strcmp(args[0], "env"))
		ft_env(data, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(args[0], "unset"))
		main_unset(data, args);
	else if (!ft_strcmp(args[0], "export"))
		main_export(data, args);
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
	int	fdout;
	int	fdin;
	
	if (actual->prev_out)
		fdout = open(actual->prev_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (actual->prev_d_out)
		fdout = open(actual->prev_d_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (actual->prev_in)
		fdin = open(actual->prev_in, O_RDONLY);
	if (fdout < 0)
		printf("%s, %s\n", actual->prev_out, actual->prev_d_out);
	if (actual->prev_out || actual->prev_d_out)
	{
		dup2(fdout, STDOUT);
		dup2(fdout, STDERR);
	}
	if (actual->prev_in)
		dup2(fdin, STDIN);
	if (fdout)
		close(fdout);
	if (fdin)
		close(fdin);
}

static void	redirection2(t_token *actual)
{
	int	fd;

	if (actual->next_out)
		fd = open(actual->next_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (actual->next_d_out)
		fd = open(actual->next_d_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (actual->next_out || actual->next_d_out)
	{
		dup2(fd, STDOUT);
		dup2(fd, STDERR);
	}
	if (fd)
		close(fd);
}

static int	child(t_data *data, t_token *actual, int i)
{
	char	*bin;
	int		fd;

	if (actual->prev_in || actual->prev_out || actual->prev_d_out)
		redirection(actual);
	if (actual->prev_pipe)
	{
		dup2(to_prev_command(actual)->pipes[0] , STDIN);
	}
	if (actual->next_pipe && !(actual->prev_d_out || actual->prev_out))
	{
		
		if (dup2(actual->pipes[1], STDOUT) < 0)
			printf("error\n");
		close(actual->pipes[1]);
		close(actual->pipes[0]);
	}
	else if (actual->next_out || actual->next_d_out)
		redirection2(actual);
	bin = get_bin_path(actual->args[0]);
	if (bin == NULL)
		bin = actual->args[0];
	if (check_built_in(data, actual->args) == 0)
	{
		if (execve(bin, actual->args, NULL) == -1)
		{
			if (errno == 2)
				printf("minishell: command not found: %s\n", actual->args[0]);
			else
				perror("minishell");
		}
	}
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
	//signal(SIGQUIT, SIG_IGN);
	if (actual->prev_pipe)
		close(to_prev_command(actual)->pipes[0]);
	if (actual->next_pipe || actual->prev_pipe)
		close(actual->pipes[1]);	
	if (actual->id == data->nb_command - 1)
		{
		//dup2(data->pipes[1], 0);
		//close(data->pipes[0]);
			while (i < data->nb_command)
			{
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
	if (actual->next_pipe || actual->prev_pipe)
		error = pipe(actual->pipes);
	if (error != 0)
		return (1);
	data->pid[i] = fork();
	if (data->pid[i] == 0)
		child(data, actual, i);
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		parent(data, actual);
		signal(SIGQUIT, signal_handler);
		signal(SIGINT, signal_handler);
	}
	return (0);
}

static void	pre_check_builtins(t_data *data, t_token *actual, int i)
{
	if (!ft_strcmp(actual->args[0], "cd"))
	{
		if (data->nb_command > 1)
			exe_pipe(data, actual, i);
		/*data->ret =*/ main_cd(data, actual->args);
	}
	/*else if (!ft_strcmp(command, "echo"))
	{
		exe_pipe(data, actual, i);
	}*/
	else if (!ft_strcmp(actual->args[0], "unset"))
	{
		exe_pipe(data, actual, i);
		/*data->ret = */main_unset(data, actual->args);
	}
	else if (!ft_strcmp(actual->args[0], "export") && actual->args[1])
	{
		exe_pipe(data, actual, i);
		/*data->ret = */main_export(data, actual->args);
	}
	else if (actual->content == NULL)
		data->ret = 127;
	else
		data->ret = exe_pipe(data, actual, i);
}

int	execution(t_data *data)
{
	char	*bin;
	data->actual = data->first;
	if (data->actual->type != COMMAND)
		data->actual = to_next_command(data->actual);
	while (data->command_nb < data->nb_command)
	{
		pre_check_builtins(data, data->actual, data->command_nb);
		data->command_nb++;
		data->actual = to_next_command(data->actual);
		if (!data->actual)
			break;
	}
	free(data->pid);
	return (0);
}