/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:46:47 by zyasuo            #+#    #+#             */
/*   Updated: 2022/04/25 18:24:41 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *error)
{
	write(2, error, ft_strlen(error));
}

void	exec_input(char **input, char **envp)
{
	if (!ft_strcmp("pwd", input[0]))
		mini_pwd();
	else if (!ft_strcmp("exit", input[0]))
		shell_exit(0);
	else if (!ft_strcmp("clear", input[0]))
		mini_clear();
	else if (!ft_strcmp("cd", input[0]))
		mini_cd(input);
	else if (!ft_strcmp("echo", input[0]))
		mini_echo(input);
	else if (!ft_strcmp("env", input[0]))
		mini_env(envp);
	else
		print_error("Such words are beyond my comprehension\n");
}
	// else if ("export")
	// 	export();
	// else if ("unset")
	// 	unset();

// int	env_utils(char **envp)
// {
// 	if (!ft_strcmp("env"))
// }

void	exec_child(char **input, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("Failed forking child\n");
		return ;
	}
	if (!pid)
	{
		if (execve(input[0], input, envp) < 0)
			perror(input[0]);
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}
