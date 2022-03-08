/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:21:16 by elouchez          #+#    #+#             */
/*   Updated: 2022/02/28 18:21:16 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler_bis(int sig)
{
	if (sig == SIGQUIT)
	{
		write(2, "\b\b  \b\b", 6);
		return ;
	}
	else
	{
		write(2, "\b\b  ", 4);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	signal_heredoc(int sig)
{
	(void)sig;
	//signal_handler(sig);
	g_pid = -1000;
}

void	signal_handler(int sig)
{
	if (g_pid != 0)
	{
		if (sig == SIGQUIT)
		{
			kill(g_pid, SIGQUIT);
			write(1, "Quit\n", 8);
			rl_on_new_line();
			rl_replace_line("", 0);
			g_pid = -1;
			return ;
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			return ;
		}
	}
	else
	{
		signal_handler_bis(sig);
	}
}

/*static void	sighandl(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_pid == 0)
		rl_redisplay();
}

static void	quithandler(void)
{
	if (g_pid != 0)
	{
		kill(g_pid, SIGQUIT);
		write(1, "Minishell quit, core dumped\n", 28);
		g_pid = -1;
	}
}

void	signal_handler(int c)
{
	if (c == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		quithandler();
		return ;
	}
	else if (c == SIGINT)
	{
		write(1, "\b\b  ", 4);
		sighandl();
		return ;
	}
}*/
