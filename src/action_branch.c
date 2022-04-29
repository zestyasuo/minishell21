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

void	action_branch(t_mini *shell, char **envp)
{
	char	**arr;
	int		pid;
	int		i;
	t_list	*lst;

	i = 0;
	lst = shell->args->content;
	arr = malloc(sizeof(*arr) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		arr[i] = lst->content;
		lst = lst->next;
		i++;
	}
	arr[i] = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(arr[0], &arr[1], envp))
			perror(arr[0]);
		execve("minishell", envp, envp);
	}
	else
		waitpid(0, 0, 0);
	free(arr);
}
