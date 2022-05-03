/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:07:22 by mnathali          #+#    #+#             */
/*   Updated: 2022/04/30 01:12:04 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_returned_value(t_list *env_list, unsigned char num)
{
	t_variable	*var;

	while (env_list->next)
		env_list = env_list->next;
	var = env_list->content;
	if (var->value)
		free(var->value);
	var->value = ft_itoa(num);
}

void	free_array(char	**arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
	return ;
}

void run_builtin(char **arr, char **envp)
{
	(void)arr;
	(void)envp;
	return ;
}

int ft_isstr(char **arr, char *str)
{
	int	i;
	
	i = 0;
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], str))
			return (1);
		i++;
	}
	return (0);
}

void	change_in(char **arr, char **envp, int *pipe)
{
	int	fd;

	fd = open(arr[1], O_RDONLY);
	if (fd < 0)
		perror(arr[1]);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	if (arr && arr[2] && execve(arr[2], &arr[2], envp))
		perror(arr[2]);
	free(arr);
	free(pipe);
	execve("./minishell", envp, envp);
}

void	change_out(char **arr, char **envp, int *pipe)
{
	int	fd;
	int	i;

	i = 0;
	while (ft_strcmp(arr[i], ">"))
		i++;
	fd = open(arr[i + 1], O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		perror(arr[i + 1]);
	else
		dup2(fd, STDOUT_FILENO);
	arr[i] = 0;
	close(fd);
	if (execve(arr[0], &arr[0], envp))
		perror(arr[0]);
	free(arr);
	free(pipe);
	execve("./minishell", envp, envp);
}

char	**get_args_to_exec(t_list *column)
{
	int		i;
	t_list	*lst;
	char	**args;

	i = 0;
	lst = column->content;
	args = malloc(sizeof(*args) * (ft_lstsize(lst) + 1));
	if (!args)
		return (0);
	while (lst)
	{
		args[i] = lst->content;
		lst = lst->next;
		i++;
	}
	args[i] = 0;
	return (args);
}

void run_bins(t_list *column, char **envp, int *fd, int i)
{
	char **arr;

	if (column->next)
		dup2(fd[2 * i + 1], STDOUT_FILENO);
	if (i)
		dup2(fd[2 * i - 2], STDIN_FILENO);
	arr = get_args_to_exec(column);
	if (!ft_strcmp(arr[0], "<"))
		change_in(arr, envp, fd);
	else if (ft_isstr(arr, ">"))
		change_out(arr, envp, fd);
	if (arr && arr[0] && arr[0][0] != '.' && arr[0][1] != '/')
		run_builtin(arr, envp);
	else if (arr && arr[0] && execve(arr[0], &arr[0], envp))
		perror(arr[0]);
	free(arr);
	free(fd);
	execve("./minishell", envp, envp);
}

void	action_branch(t_mini *shell, char **envp)
{
	int		*fd;
	int		pid;
	int		size;
	t_list	*columns;
	int		i;

	i = 0;
	columns = shell->args;
	size = ft_lstsize(columns);
	fd = malloc(sizeof(*fd) * (size * 2 - 2));
	if (!fd)
		return ;
	while (i / 2 != size - 1)
	{
		pipe(&fd[i]);
		i += 2;
	}
	i = 0;
	while (columns)
	{
		pid = fork();
		if (pid < 0)
			break ;
		else if (pid == 0)
			run_bins(columns, envp, fd, i);
		columns = columns->next;
		i++;
	}
	free(fd);
	while (i)
	{
		waitpid(0, &pid, 0);
		i--;
	}
	change_returned_value(shell->var_list, WEXITSTATUS(pid));//////////////////////////////////
}
