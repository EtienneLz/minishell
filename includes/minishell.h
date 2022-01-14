/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:48 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/13 18:31:19 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
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

typedef struct	s_export
{
	char	**args;
	int		check;
	int		valid_args;
	int		equal;
}				t_export;

typedef struct	s_data
{
	t_token		*first;
	t_export	export;
	char		**envp;
	int			envp_i;
}				t_data;
/*
** Built-in functions 
*/
void	init(t_data *data);
void	env(t_data *data);
void	echo(char *s, int flag_n);
void	pwd(void);
void	ft_exit(t_data *data);
void	export_no_arg(t_data *data);
void	export_args(t_data *data, char **args);
void    main_check(t_data *data, char **args);
void    check_export_args(t_data *data, char **args);
void 	copy_equal(t_data *data);
char	**copy_args(t_data *data, char **str, char **dest, int *i)
;int		cmp_arg(t_data *data, char *str);


t_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_token **alst, t_token *new);
void	split_command(t_data *data, char *command);
void	ft_lstfree(t_data *data);

#endif