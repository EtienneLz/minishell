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
		signal_handler_bis(sig);
	}
}
