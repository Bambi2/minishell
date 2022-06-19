/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:33 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 20:41:33 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <history.h>
# include <readline.h>
# include <termios.h>

# define PROMPT "minishell > "

# define WORD 1
# define FIELD 2
# define DFIELD 3
# define TRUNC 40
# define APPEND 50
# define READ 60
# define HEREDOC 70
# define PIPE 80
# define SPACER 90
# define CMD 10
# define ARG 20
# define LIMITER 100
# define OFILE 200
# define IFILE 300

typedef struct s_pipes
{
	int				fd[2];
}	t_pipes;

typedef struct s_token
{
	int				token_type;
	char			*token;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	char	**envp;
	t_token	*tokens;
	int		fdin;
	int		fdout;
	int		is_pipe;
	int		is_wstatus;
	t_pipes	*pipes;
	int		*pids;
	int		count_of_cmd;
	int		count_of_pipe;
	int		currentp;
	int		currentcmd;
}	t_minishell;

typedef struct s_termflag
{
	int	last_exit_status;
	int	is_reading;
}	t_termflag;

extern t_termflag	g_termflag;

t_token		*lekser(char *str, t_minishell *minishell);

// lekser func!
int			is_newtoken(char c);
int			get_type(char *sep);
char		*tokenizer(char const *s, int *start, char *sep);
void		find_sep(char *str, int i, char **sep);
void		skip_space(char *str, int *i);

// parser func!
int			change_tokens(t_token *lst, t_token *prev, int *cmd_flag);
void		open_evar(t_token **head, t_minishell *minishell);
void		remove_spaces(t_token **token_list);

// token list func!
int			lstadd_back(t_token **lst, t_token *new);
void		lstclear(t_token **lst, void (*del)(void *));
t_token		*lstnew(int token_type, char *token);

// func for test!
void		ft_printlist(t_token *lst);

// relib func
int			strjoin(char **s1, char *s2);
char		*strtrim(char *str);

//init minishell

t_minishell	*init_minishell(char **envp);

//executor

void		executor(t_minishell *minishell);

//handle pipes
int			handle_pipes(t_minishell *minishell);

//set input

int			set_input(t_minishell *minishell);
int			count_inputs(t_token *tokens);
int			reopen(int fdin);
int			is_limiter(char *limiter, char *line);
int			rewrite(int fdin);

//handle cmd

int			handle_cmd(t_minishell *minishell, t_token *cmd);

//handle built in

int			handle_built_in(t_minishell *minishell, t_token	*token);
int			is_built_in(t_token *token);

//handle binary

int			handle_bin(t_minishell *minishell, t_token *token);

//builtins

void		echo(char **argv);
void		cd(t_minishell *minishell, char **argv);
void		pwd(void);
void		export(t_minishell *minishell, char **argv);
void		env(t_minishell *minishell);
void		unset(t_minishell *minishell, char **argv);
void		exit_cmd(char **argv);

//get path

char		**get_path(t_minishell *minishell, char *cmd);

//get arguments

char		**get_arguments(t_token *token, char *path);

//environment

char		*get_env_var(char **envp, char *name);
int			get_env_index(char **envp, char *var_name);
int			change_env(t_minishell *minishell,
				char *var_name, char *new_var_value);
int			add_env_var(t_minishell *minishell,
				char *var_name, char *var_value);
int			remove_env_var(t_minishell *minishell,
				char *var_name);

//signal handling

void		signal_handling(int sig);
int			set_signals(void);

//string utils

void		free_strings(char **strings, int i);
void		free_strings_error(char **strings, int i);
char		**copy_strings(char **strings);
int			get_strings_count(char **strings);
char		**allocate_extra_space(char **old_arr, int *count);
char		**remove_string(char **old_arr, int index);
char		**allocate_less_strings(char **arr, int *count);

char		*custom_readline(t_minishell *minishell, char *prompt);

#endif