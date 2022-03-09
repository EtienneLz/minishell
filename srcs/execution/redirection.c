/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:11:33 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:11:33 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirection(t_token *actual)
{
	int	fdout;
	int	fdin;

	fdout = 0;
	fdin = 0;
	if (actual->prev_out)
		fdout = open(actual->prev_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (actual->prev_d_out)
		fdout = open(actual->prev_d_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (actual->prev_in)
		fdin = open(actual->prev_in, O_RDONLY);
	if (fdout < 0 || fdin < 0)
		print_error("error: File opening failed\n");
	if (actual->prev_out || actual->prev_d_out)
	{
		dup2(fdout, STDOUT);
		dup2(fdout, STDERR);
	}
	if (actual->prev_in)
		dup2(fdin, STDIN);
	if (fdout > 0)
		close(fdout);
	if (fdin > 0)
		close(fdin);
}

void	redirection2(t_token *actual)
{
	int	fdout;
	int	fdin;

	fdout = 0;
	fdin = 0;
	if (actual->next_out)
		fdout = open(actual->next_out, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (actual->next_d_out)
		fdout = open(actual->next_d_out, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (actual->next_in)
		fdin = open(actual->next_in, O_RDWR | O_APPEND, 0666);
	if (fdout < 0 || fdin < 0)
		print_error("File opening failed\n");
	if (actual->next_out || actual->next_d_out)
	{
		dup2(fdout, STDOUT);
		dup2(fdout, STDERR);
	}
	if (actual->next_in)
		dup2(fdin, STDIN);
	if (fdout)
		close(fdout);
	if (fdin)
		close(fdin);
}

int	ret_status(t_data *data, int status, int i)
{
	int	ret;
	int	ex;

	ret = 0;
	ex = 0;
	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status);
		if (ret != 131)
			return (ret += 128);
	}
	if (i == data->nb_command - 1)
	{
		ex = WIFEXITED(status);
		if (ex > -1)
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

void	child_pipe(t_token *actual)
{
	if (dup2(actual->pipes[1], STDOUT) < 0)
		print_error(" \n");
	close(actual->pipes[1]);
	close(actual->pipes[0]);
}
