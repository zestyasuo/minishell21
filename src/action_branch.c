/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_branch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 23:07:22 by mnathali          #+#    #+#             */
/*   Updated: 2022/05/05 01:34:53 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_exit_code(t_list *var_list)
{
	t_list	*lst;
	t_variable	*var;

	lst = var_list;
	while (lst)
	{
		var = lst->content;
		free(var->name);
		free(var->value);
		free(var);
		lst = lst->next;
		free(var_list);
		var_list = lst;
	}
	exit(0);
}

void	check_returned_value(t_list *env_list)
{
	t_list		*var_list;
	t_variable	*var;

	var_list = env_list;
	while (env_list && env_list->next)
		env_list = env_list->next;
	var = env_list->content;
	if (!ft_strcmp(var->value, "255"))
		get_exit_code(var_list);
	printf("returned = %s | %s\n", var->name, var->value);///////////////
	return ;
}

void	change_returned_value(t_list *env_list, unsigned char num)
{
	t_variable	*var;

	while (env_list && env_list->next)
		env_list = env_list->next;
	var = env_list->content;
	if (var->value)
		free(var->value);
	var->value = ft_itoa(num);
}

void	close_fd(int *fd, int size)
{
	if (fd == 0)
		return ;
	while (size > 0)
	{
		size--;
		close(2 * size + 1);
		close(2 * size);
	}
	free(fd);
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

int ft_isstr(t_list *column, char *str)
{
	t_list	*lst;
	
	lst = column->content;
	while (lst)
	{
		if (!ft_strcmp(lst->content, str))
			return (1);
		lst = lst->next;
	}
	return (0);
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

char	**change_in(t_list *column)
{
	int		fd;
	t_list	*lst_1;
	t_list	*lst_2;
	
	lst_1 = column->content;
	lst_2 = column->content;
	while (ft_strcmp(lst_1->content, "<"))
		lst_1 = lst_1->next;
	if (lst_1->next == 0 && ft_putstr_fd("minishell: syntax error\n", 2))
		return (0);
	fd = open(lst_1->next->content, O_RDONLY);
	if (fd < 0)
	{
		perror(lst_1->next->content);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (lst_1 == lst_2)
		column->content = lst_1->next->next;
	while (lst_2 != lst_1 && lst_2->next != lst_1)
		lst_2 = lst_2->next;
	if (lst_2 != lst_1)
		lst_2->next = lst_1->next->next;
	lst_1->next->next = 0;
	ft_lstclear(&lst_1, free);
	return (get_args_to_exec(column));
}

char	**change_out(t_list *column)
{
	int		fd;
	t_list	*lst_1;
	t_list	*lst_2;
	
	lst_1 = column->content;
	lst_2 = column->content;
	while (ft_strcmp(lst_1->content, ">") && ft_strcmp(lst_1->content, ">>"))
		lst_1 = lst_1->next;
	if (lst_1->next == 0 && ft_putstr_fd("minishell: syntax error\n", 2))
		return (0);
	if (ft_strcmp(lst_1->content, ">") == 0)
		fd = open(lst_1->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(lst_1->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(lst_1->next->content);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (lst_1 == lst_2)
		column->content = lst_1->next->next;
	while (lst_2 != lst_1 && lst_2->next != lst_1)
		lst_2 = lst_2->next;
	if (lst_2 != lst_1)
		lst_2->next = lst_1->next->next;
	lst_1->next->next = 0;
	ft_lstclear(&lst_1, free);
	return (get_args_to_exec(column));
}

char	**set_delim(t_list *column)
{
	int		fd;
	t_list	*lst_1;
	t_list	*lst_2;
	char	*str[2];
	
	lst_1 = column->content;
	lst_2 = column->content;
	while (ft_strcmp(lst_1->content, "<<"))
		lst_1 = lst_1->next;
	if (lst_1->next == 0 && ft_putstr_fd("minishell: syntax error\n", 2))
		return (0);
	fd = open("/tmp/here-doc-minishell", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(lst_1->next->content);
		return (0);
	}
	str[0] = readline("> ");
	while (ft_strcmp(str[0], lst_1->next->content))
	{
		write(fd, str[0], ft_strlen(str[0]));
		write(fd, "\n", 1);
		free(str[0]);
		str[0] = readline("> ");
	}
	free(str[0]);
	close(fd);
	if (lst_1 == lst_2)
		column->content = lst_1->next->next;
	while (lst_2 != lst_1 && lst_2->next != lst_1)
		lst_2 = lst_2->next;
	if (lst_2 != lst_1)
		lst_2->next = lst_1->next->next;
	lst_1->next->next = 0;
	ft_lstclear(&lst_1, free);
	fd = open("/tmp/here-doc-minishell", O_RDONLY);
	if (fd < 0)
	{
		perror(lst_1->next->content);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (get_args_to_exec(column));
}

char	**change_in_out_delim(t_list *column)
{
	char	**arr;
	
	arr = 0;
	if (ft_isstr(column, "<<"))
	{
		arr = set_delim(column);
		if (!arr)
			return (0);
	}
	else if (ft_isstr(column, "<"))
	{
		arr = change_in(column);
		if (!arr)
			return (0);
	}
	if (ft_isstr(column, ">") || ft_isstr(column, ">>"))
	{
		if (arr)
			free(arr);
		arr = change_out(column);
		if (!arr)
			return (0);
	}
	return (arr);
}

void run_bins(t_list *column, char **envp, int *fd, int i)
{
	char **arr;

	if (column->next)
		dup2(fd[2 * i + 1], STDOUT_FILENO);
	if (i)
		dup2(fd[2 * i - 2], STDIN_FILENO);
	if (ft_isstr(column, "<") || ft_isstr(column, ">")
		|| ft_isstr(column, ">>") || ft_isstr(column, "<<"))
		arr = change_in_out_delim(column);
	else
		arr = get_args_to_exec(column);
	if (fd)
		free(fd);
	if (arr && arr[0] && (ft_strncmp(arr[0], "./", 2) && ft_strncmp(arr[0], "/bin/", 5)))
		exec_input(arr, envp);
	else if (arr && arr[0] && execve(arr[0], &arr[0], envp))
		perror(arr[0]);
	if (arr)
		free(arr);
	exit(127);
	//execve("./minishell", envp, envp);
}

void	action_branch(t_mini *shell, char **envp)
{
	int		*fd;
	int		pid;
	int		size;
	t_list	*columns;
	int		i;

	i = 0;
	fd = 0;
	columns = shell->args;
	size = ft_lstsize(columns);
	if (ft_lstsize(columns) - 1 > 0)
		fd = malloc(sizeof(*fd) * (size * 2 - 2));
	if (size - 1 > 0 && !fd)
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
	while (i)
	{
		waitpid(0, &pid, 0);
		i--;
	}
	close_fd(fd, size);
	change_returned_value(shell->var_list, WEXITSTATUS(pid));
}
