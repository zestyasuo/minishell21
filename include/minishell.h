/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:10:08 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/10 21:06:24 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../ft_printf/include/ft_printf.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# define ARGERROR "Error. Minishell shall only start without arguments.\n"
# define MAXARGLEN 10
# define MAXARGS 100
# define SHELLNAME "minishell$ "

typedef struct s_variable {
	char				*name;
	char				*value;
}	t_variable;

typedef struct s_mini {
	t_list		*args;
	t_list		*var_list;
}	t_mini;

void		mini_clear(void);
void		mini_pwd(void);
int			mini_cd(char **path, char **envp);
void		mini_echo(char **args);
int			shell_exit(t_mini *shell, t_list *envp);
void		mini_env(t_list *envp);
int			mini_unset(t_mini *shell, t_list *envp);
int			mini_export(t_mini *shell, t_list *envp);

t_list		*parse_args(char *input);
t_list		*get_args(t_list *input);
void		destroy_var(void *p);
t_list		*get_environ(char **envp);
void		expand_variables(t_mini *shell);
void		print_variable(void *pointer);
t_variable	*new_var(char *name, char *value);

int			create_shell(t_mini **pointer, char **envp);
int			read_input(char **input);
void		exec_input(char **input, t_list *envp);
void		print_error(char *error);
void		exec_child(char **input, char **envp);
void		print_content(void *content);
void		clear_content(void *lst);
int			add_arg(t_list **list, char *arg);
void		remove_backslash(void *p);

void		print_content(void *content);
void		print_args(void *args);
void		clear_content(void *lst);
t_list		*get_variable_by_name(t_list *var_list, char *name);

void		action_branch(t_mini *shell, t_list *envp);
void		change_var_value(t_list *env_list, char *name, char *value);
void		check_returned_value(t_list *env_list, t_list *envp);
char		**change_in_out_delim(t_list *column);
char		**get_args_to_exec(t_list *lst);
void		remove_elements(t_list *column, t_list *lst_1);
char		**set_delim(t_list *column);
void		close_fd(int *fd, int size);
int			ft_isstr(t_list *column, char *str);
void		remove_quotes(void *content);
void		unset_shell_atrr(void);
void		set_shell_attr(void);

t_list		*ft_arrdup_to_lst(char **arr_1);
void		free_arr(char **arr);
int			add_new_variable(t_mini *shell);

#endif
