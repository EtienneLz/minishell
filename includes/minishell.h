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
# include "../libft/libft.h"
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 2048
# define STRING 's'
# define STRING_SIMPLE 'q'
# define COMMAND 'c'
# define OPTION 'o'
# define PIPE 'p'
# define R_ARROW 'r'
# define L_ARROW 'l'
# define RR_ARROW 'x'
# define LL_ARROW 'y'

typedef struct s_token
{
	struct s_token	*prev;
	char			*content;
	char			type;
	int				id;
	char			**args;
	char			*prev_out;
	char			*prev_d_out;
	char			*prev_in;
	char			*next_out;
	char			*next_d_out;
	char			*next_in;
	int				prev_pipe;
	int				next_pipe;
	int				pipes[2];
	struct s_token	*next;
}				t_token;

typedef struct s_export
{
	char		**args;
	int			check;
	int			valid_args;
	int			equal;
}				t_export;

typedef struct s_unset
{
	int			is_unset;
	int			check;
	int			valid_args;
	char		**args;
	int			ret;
}				t_unset;

typedef struct s_cd
{
	int			ret;
	char		*home;
}				t_cd;

typedef struct s_data
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
	int			nb_command;
	int			tmpin;
	int			tmpout;
	char		*buffer;
	char		quote_type;
	int			ret;
	int			last_ret;
	int			nb_infiles;
	char		**infile;
	int			nb_outfiles;
	char		**outfile;
	int			last_out;
	char		*tmp_var;
	int			heredoc;
	int			heredoc_nb;
	pid_t		*pid;
}				t_data;

int	g_pid;
/*
** Errors functions 
*/
void	cd_error(t_data *data, char *str);
void	unset_error(t_data *data, char *str);
void	export_error(t_data *data, char *str);
void	alloc_error(t_data *data, char *cmd);

/*
** Built-ins functions 
*/
int		ft_env(t_data *data, char **args);
int		ft_echo(t_data *data, char **args);
int		ft_pwd(void);
void	ft_exit(t_data *data, char **args);

/*
** utils built-ins functions
*/
int		if_equal(t_data *data, char *s1, char *s2);
char	*join_arg(char *s1, char *s2);

/*
** Cd functions
*/
void	main_cd(t_data *data, char **args);
void	change_pwd_vars(t_data *data, char *oldpwd, char *pwd);
char	*cd_join(char *dir, char *arg, char *new_dir);
char	*if_tilde(t_data *data, char *arg);

/*
** Export functions
*/
int		main_export(t_data *data, char **args);
void	export_main_check(t_data *data, char **args);
char	**copy_env(t_data *data, char **tab, char **dest, int *i);
char	**sort_env_atoz(char **tab, int len);
void	copy_equal(t_data *data);
int		cmp_export_arg(t_data *data, char *str);

/*
** Unset functions
*/
int		main_unset(t_data *data, char **args);
void	unset_main_check(t_data *data, char **args);

/*
** utils functions
*/
void	free_tab(char **tab);
t_token	*ft_lstnew(t_data *data, char *content);
void	ft_lstadd_back(t_token **alst, t_token *new);
void	ft_lstfree(t_data *data);
char	***split_arg(t_data *data);
void	check_exit(t_data *data);
char	*treat_var(char *var);
char	*check_exist(t_data *data, char *var);

void	signal_handler(int sig);
void	init(t_data *data);
void	prompt(t_data *data);
void	reset(t_data *data);
int		lexer(t_data *data);
int		execution(t_data *data);
void	minifree(t_data *data);
void	splitted_args_free(char ***tab);
int		split_command(t_data *data, char *command);
void	check_var(t_data *data, char *str, t_token *actual);
int		get_quoted(char *command, int i, char quote);
int		check_pipe(t_token	*actual);
t_token	*to_next_command(t_token *actual);
void	expand(t_data *data);
char	*check_quotes(t_data *data, char *str);
char	*line_prompt(char *prompt);
void	print_error(char *error_str);
char	is_redirection(char *str);
int		is_arrow(char *str);
int		is_string(char type);
void	structure(t_data *data);
t_token	*to_prev_command(t_token *actual);
void	remove_quotes(t_data *data);
void	get_sep(t_data *data);

#endif