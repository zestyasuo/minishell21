/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 00:31:54 by mnathali          #+#    #+#             */
/*   Updated: 2022/05/07 00:42:38 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	got_exit_code(t_list *var_list)
{
	t_list		*lst;
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
	//printf("returned = %s | %s\n", var->name, var->value);///////////////
	if (!ft_strcmp(var->value, "255"))
		got_exit_code(var_list);
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
	size--;
	while (size > 0)
	{
		size--;
		close(fd[2 * size + 1]);
		close(fd[2 * size]);
	}
	free(fd);
}

int	ft_isstr(t_list *column, char *str)
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