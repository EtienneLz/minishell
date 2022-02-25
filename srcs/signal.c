/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:05:08 by mseligna          #+#    #+#             */
/*   Updated: 2022/02/25 18:10:04 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*static void	do_ctrl_c(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_pid == 0)
	{
		rl_redisplay();
	}
	//signal(SIGINT, signal_handler);
}

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		//printf("pid \\\ = %d\n", g_pid);
		//signal(SIGQUIT, SIG_IGN);
		if (g_pid != 0)
		{
			//signal(SIGQUIT, SIG_IGN);
			write(1, "Quit: 3\n", 8);
			kill(g_pid, SIGQUIT);
			//write(1, "^\\\Quit: 3\n", 11);
			g_pid = -1;
			return ;
		}
		else if (g_pid == 0)
		{
			write(2, "\t\t\b\b\b\b\b  \b\b", 11);
		}
		//signal(SIGQUIT, signal_handler);
	}
	else if (sig == SIGINT)
	{
		write(2, "\t\t\b\b\b\b\b  ", 9);
		do_ctrl_c();
		return ;
	}
}*/

void	signal_handler(int sig)
{
	if (g_pid != 0)
	{
		if (sig == SIGQUIT)
		{
			kill(g_pid, SIGQUIT);
			write(1, "Quit: 3\n", 8);
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
		if (sig == SIGQUIT)
		{
			write(2, "\t\t\b\b\b\b\b  \b\b", 11);
			return ;
		}
		else
		{
			write(2, "\t\t\b\b\b\b\b  ", 9);
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
	}
}
