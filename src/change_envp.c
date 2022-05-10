/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 09:53:17 by mnathali          #+#    #+#             */
/*   Updated: 2022/05/10 21:01:34 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*looking_for_var(t_list *envp_list, char *str)
{
	t_variable	*var;

	while (envp_list)
	{
		var = envp_list->content;
		if (!ft_strcmp(var->name, str))
			break ;
		envp_list = envp_list->next;
	}
	if (envp_list)
		return (var->value);
	return (0);
}

int	add_new_variable(t_mini *shell)
{
	int		i;
	char	*str;
	char	*name;
	char	*value;

	str = ((t_list *)(shell->args->content))->content;
	value = ft_strchr(str, '=') + 1;
	i = value - str - 1;
	if (i == 0 || !*value || !ft_strncmp("?=", str, 2))
		return (0 * ft_putstr_fd("error : command not found\n", 2) + 127);
	name = malloc(sizeof(*name) * (i + 1));
	if (!name)
		return (1);
	name[i] = 0;
	while (i--)
		name[i] = str[i];
	if (looking_for_var(shell->var_list, name))
	{
		change_var_value(shell->var_list, name, ft_strdup(value));
		free(name);
	}
	else
		ft_lstadd_front(&shell->var_list,
			ft_lstnew(new_var(name, ft_strdup(value))));
	return (0);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

t_list	*ft_arrdup_to_lst(char **arr)
{
	t_list	*lst;
	t_list	*new;
	int		i;

	lst = 0;
	i = ft_arrlen(arr);
	if (!i)
		return (0);
	while (i)
	{
		i--;
		new = ft_lstnew(ft_strdup(arr[i]));
		if (!new)
		{
			ft_lstclear(&lst, free);
			return (0);
		}
		ft_lstadd_front(&lst, new);
	}
	return (lst);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}
