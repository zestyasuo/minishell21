/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:07:22 by mnathali          #+#    #+#             */
/*   Updated: 2022/05/10 21:17:12 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**replace_fd(t_list *column, int *fd, int i)
{
	char	**arr;

	if (column->next)
		dup2(fd[2 * i + 1], STDOUT_FILENO);
	if (i)
		dup2(fd[2 * i - 2], STDIN_FILENO);
	if (ft_isstr(column, "<") || ft_isstr(column, ">")
		|| ft_isstr(column, ">>") || ft_isstr(column, "<<"))
		arr = change_in_out_delim(column);
	else
		arr = get_args_to_exec(column->content);
	return (arr);
}

void	run_bins(char **arr, t_list *envp, int *fd, int size)
{
	char	**arr_envp;

	arr_envp = get_args_to_exec(envp);
	if (arr && arr[0] && (ft_strncmp(arr[0], "./", 2)
			&& ft_strncmp(arr[0], "/bin/", 5)))
		exec_input(arr, envp);
	else if (arr && arr[0] && execve(arr[0], &arr[0], arr_envp))
		perror(arr[0]);
	free_arr(arr);
	free_arr(arr_envp);
	close_fd(fd, size);
	exit(127);
}

int	*create_pipes(t_list *columns)
{
	int	i;
	int	*fd;
	int	size;

	i = 0;
	size = ft_lstsize(columns);
	if (size < 2)
		return (0);
	fd = malloc(sizeof(*fd) * (size * 2 - 2));
	if (!fd)
		return (0);
	while (i / 2 != size - 1)
	{
		pipe(&fd[i]);
		i += 2;
	}
	return (fd);
}

int	children_to_exec(t_list *columns, int *fd, t_list *envp)
{
	int	i;
	int	size;
	int	pid;

	i = 0;
	size = ft_lstsize(columns);
	while (columns)
	{
		pid = fork();
		if (pid < 0)
			break ;
		else if (pid == 0)
			run_bins(replace_fd(columns, fd, i), envp, fd, size);
		columns = columns->next;
		i++;
		waitpid(0, &pid, 0);
		if (WEXITSTATUS(pid) == 127)
			break ;
	}
	close_fd(fd, size);
	if (pid < 0)
		return (127);
	return (WEXITSTATUS(pid));
}

void	action_branch(t_mini *shell, t_list *envp)
{
	int		*fd;
	int		status;
	t_list	*arg_list;

	unset_shell_atrr();
	arg_list = (t_list *)(shell->args->content);
	fd = create_pipes(shell->args);
	if (!fd && shell->args->next)
		return ;
	if (shell->args->next == 0 && !ft_strcmp(arg_list->content, "cd"))
		mini_cd(get_args_to_exec(shell->args->content), get_args_to_exec(envp));
	if (!shell->args->next && ft_strchr(arg_list->content, '=')
		&& !ft_strchr(arg_list->content, '.')
		&& !ft_strchr(arg_list->content, '/') && !arg_list->next)
		status = add_new_variable(shell);
	else if (shell->args->next == 0 && !ft_strcmp(arg_list->content, "export"))
		status = mini_export(shell, envp);
	else if (shell->args->next == 0 && !ft_strcmp(arg_list->content, "unset"))
		status = mini_unset(shell, envp);
	else if (shell->args->next == 0 && !ft_strcmp(arg_list->content, "exit"))
		status = shell_exit(shell, envp);
	else
		status = children_to_exec(shell->args, fd, envp);
	change_var_value(shell->var_list, "?", ft_itoa(status));
}
