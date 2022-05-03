/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:43:12 by zyasuo            #+#    #+#             */
/*   Updated: 2022/04/22 19:25:33 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*valid_args(t_list *args)
{
	t_list	*current_list;
	t_list	*current_el;
	int		valid;

	current_list = args;
	valid = 1;
	while (current_list)
	{
		current_el = current_list->content;
		if (ft_strchr(current_el->content, '|'))
			valid = 0;
		current_list = current_list->next;
	}
	if (valid)
		return (args);
	ft_lstclear(&args, clear_content);
	return (0);
}

t_list	*get_args(t_list *input)
{
	t_list	*args;
	t_list	*current;
	t_list	*head;

	current = input;
	head = input;
	args = NULL;
	while (head && current->next)
	{
		if (ft_strchr(current->next->content, '|')
			&& ft_strlen(current->next->content) == 1)
		{
			ft_lstadd_back(&args, ft_lstnew(head));
			head = current->next->next;
			ft_lstdelone(current->next, free);
			current->next = NULL;
			current = head;
		}
		else
			current = current->next;
	}
	if (head)
		ft_lstadd_back(&args, ft_lstnew(head));
	return (valid_args(args));
}
