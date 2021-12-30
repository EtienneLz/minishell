/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:48 by elouchez          #+#    #+#             */
/*   Updated: 2021/12/30 18:58:47 by elouchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../42_libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 2048
# define COMMAND 'c'
# define OPTION 'o'

typedef struct	s_token
{
	char			*content;
	char			type;
	struct s_token	*next;
} 				t_token;

typedef struct	s_data
{
	t_token		*first;
}				t_data;
/*
** Built-in functions 
*/

void	echo(char *s, int flag_n);
void	pwd(void);


t_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_token **alst, t_token *new);
void	split_command(t_data *data, char *command);
void	ft_lstfree(t_data *data);

#endif