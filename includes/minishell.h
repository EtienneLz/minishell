/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseligna <mseligna@students.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:25:48 by elouchez          #+#    #+#             */
/*   Updated: 2022/01/23 12:28:18 by mseligna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h> 
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>
# include "../42_libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 2048
# define STRING 's'
# define STRING_SIMPLE 'q'
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

typedef struct	s_export
{
	char	**args;
	int		check;
	int		valid_args;
	int		equal;
}				t_export;

typedef struct  s_unset
{
	int		is_unset;
	int		check;
	int		valid_args;
	char	**args;
	int		ret;
}				t_unset;

typedef struct  s_cd
{
	int		ret;
	char	*home;
}				t_cd;

typedef struct	s_data
{
	t_token		*first;
	t_token		*actual;
	t_export	export;
	char		**envp;
	int			envp_i;
	t_unset		unset;
	t_cd		cd;
	char		***splitted_args;
	int			error;
	int			nb_pipe;
	int			command_nb;
	int			pid;
	int			tmpin;
	int			tmpout;
	char		*buffer;
	char		quote_type;
	int			ret;
	int			nb_infiles;
	char		**infile;
	int			nb_outfiles;
	char		**outfile;
	int			last_out;
	char		*tmp_var;
}				t_data;

/*
** Built-ins functions 
*/
void	env(t_data *data);
void	echo(char *s, int flag_n);
void	pwd(void);
void	ft_exit(t_data *data);
char	**copy_args(t_data *data, char **str, char **dest, int *i);

/*
** utils functions
*/

int		if_equal(t_data *data,char *s1, char *s2);
int		main_cd(t_data * data, char **args);
char	*join_arg(char *s1, char *s2);

/*
** Export functions
*/
void	main_export(t_data *data, char **args);
void	export_no_arg(t_data *data);
void	export_args(t_data *data, char **args);
void    export_main_check(t_data *data, char **args);
void    check_export_args(t_data *data, char **args);
void 	copy_equal(t_data *data);
int		cmp_export_arg(t_data *data, char *str);

/*
** Unset functions
*/
void	main_unset(t_data *data, char **args);
void	unset_main_check(t_data *data, char **args);

/*
** utils functions
*/
void	free_tab(char **tab);
t_token	*ft_lstnew(char *content);
void	ft_lstadd_back(t_token **alst, t_token *new);
void	ft_lstfree(t_data *data);
char	***split_arg(t_data *data);
void	check_exit(t_data *data);

void	init(t_data *data);
void	reset(t_data *data);
int		lexer(t_data *data);
int		execution(t_data *data);
void	minifree(t_data *data);
void	splitted_args_free(char ***tab);
int		split_command(t_data *data, char *command);
int		check_pipe(t_token	*actual);
t_token	*to_next_command(t_token *actual);
void 	expand(t_data *data);

#endif