/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elouchez <elouchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:48 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 06:46:13 by elouchez         ###   ########.fr       */
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
# include <sys/types.h>
# include <signal.h>
# include <wait.h>
# include "../42_libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 2048
# define STRING 's'
# define COMMAND 'c'
# define OPTION 'o'
# define FILE 'f'
# define PIPE 'p'
# define R_ARROW 'r'
# define L_ARROW 'l'
# define RR_ARROW 'x'
# define LL_ARROW 'y'

typedef struct	s_token
{
	char			*content;
	char			type;
	struct s_token	*next;
} 				t_token;

typedef struct	s_data
{
	t_token		*first;
	char		***splitted_args;
	int			error;
	int			nb_pipe;
}				t_data;
/*
** Built-ins functions 
*/

void	echo(char *s, int flag_n);
void	pwd(void);
void	ft_exit(t_data *data);

/*
** utils functions
*/

void	free_tab(char **tab);
t_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_token **alst, t_token *new);
void	ft_lstfree(t_data *data);
char	***split_arg(t_data *data);

int		split_command(t_data *data, char *command);
void	init(t_data *data);
int		tokenizer(t_data *data);
int		execution(t_data *data);


#endif