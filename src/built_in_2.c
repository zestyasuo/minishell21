/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:53:12 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/10 21:09:13 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_env(t_list *envp)
{
	while (envp)
	{
		ft_printf("%s\n", envp->content);
		envp = envp->next;
	}
}

int	mini_export(t_mini *shell, t_list *envp)
{
	int	i;

	(void)shell;
	(void)envp;
	i = 0;
	return (i);
}

void	remove_var_frst(t_list **lst, char *str)
{
	t_list	*elem;
	t_list	*envp;
	int		len;

	envp = *lst;
	len = ft_strlen(str);
	if (!ft_strncmp(envp->content, str, len)
		&& ft_strchr(envp->content, '=') - (char *)envp->content == len)
	{
		*lst = envp->next;
		free(envp->content);
		free(envp);
		return ;
	}
	while (envp->next)
	{
		if (!ft_strncmp(envp->next->content, str, len)
			&& ft_strchr(envp->next->content, '=')
			- (char *)envp->next->content == len)
		{
			elem = envp->next;
			envp->next = elem->next;
			free(elem->content);
			free(elem);
			break ;
		}
		envp = envp->next;
	}
	return ;
}

void	remove_var_scnd(t_list **env_lst, char *str)
{
	t_list		*lst;
	t_list		*var_lst;
	t_variable	*var;

	var_lst = *env_lst;
	if (!ft_strcmp(((t_variable *)(var_lst->content))->name, str))
	{
		*env_lst = var_lst->next;
		destroy_var(var_lst->content);
		free(var_lst);
		return ;
	}	
	while (var_lst->next)
	{
		var = var_lst->next->content;
		if (!ft_strcmp(var->name, str))
		{
			lst = var_lst->next;
			var_lst->next = lst->next;
			destroy_var(lst->content);
			free(lst);
			break ;
		}
		var_lst = var_lst->next;
	}
}

int	mini_unset(t_mini *shell, t_list *envp)
{
	t_list	*lst;

	lst = shell->args->content;
	lst = lst->next;
	if (!ft_strcmp("?", lst->content))
		return (0 * ft_putstr_fd("mshell: unset: '?' not valid\n", 2) + 1);
	while (lst)
	{
		remove_var_frst(&envp, lst->content);
		remove_var_scnd(&shell->var_list, lst->content);
		lst = lst->next;
	}
	return (0);
}
