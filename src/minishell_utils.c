/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:46:47 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/09 23:53:23 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *error)
{
	write(2, error, ft_strlen(error));
}

void	exec_input(char **input, t_list *envp)
{
	int i;
	
	i = 0;
	if (!ft_strcmp("pwd", input[0]))
		mini_pwd();
	else if (!ft_strcmp("clear", input[0]))
		mini_clear();
	else if (!ft_strcmp("cd", input[0]))
		i = mini_cd(input, 0);
	else if (!ft_strcmp("echo", input[0]))
		mini_echo(input);
	else if (!ft_strcmp("env", input[0]))
		mini_env(envp);
	else if (!ft_strcmp("exit", input[0]) || !ft_strcmp("export", input[0])
		|| !ft_strcmp("unset", input[0]))
		i = 1;
	else
	{
		print_error("Such words are beyond my comprehension\n");
		return ;
	}
	free_arr(input);
	ft_lstclear(&envp, free);
	exit(i);
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
