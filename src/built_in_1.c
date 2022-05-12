/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:50:05 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/12 15:29:00 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mini_env(t_list *envp, char *str)
{
	while (envp)
	{
		if (str && ((ft_strchr(envp->content, '=') && !str[0]) || str[0]))
			ft_printf("%s%s\n", str, envp->content);
		envp = envp->next;
	}
	return (0);
}

void	mini_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}

int	mini_cd(t_list *args, t_list *envp)
{
	int		i;
	int		code;
	char	*home_dir;

	code = 1;
	home_dir = look_var(envp, "HOME");
	i = ft_lstsize(args);
	if (i == 1 && home_dir)
		home_dir = ft_strchr(home_dir, '=') + 1;
	if (i > 2)
		print_error("cd : too many arguments\n");
	else if (i == 2 && chdir(args->next->content))
		perror("cd ");
	else if (i == 1 && chdir(home_dir))
		ft_putstr_fd("mshell : cd : HOME not set\n", 2);
	else
		code = 0;
	return (code);
}

void	mini_echo(char **args)
{
	int		i;
	int		endl;

	if (!args[1])
	{
		write(1, "\n", 1);
		return ;
	}
	endl = !ft_strncmp("-n", args[1], ft_strlen(args[1]));
	if (!args[2] && endl)
		return ;
	i = 1 + endl;
	while (args[i + 1])
		ft_printf("%s ", args[i++]);
	ft_printf("%s", args[i]);
	if (!endl)
		write(1, "\n", 1);
}

void	mini_clear(void)
{
	ft_printf("\033[H\033[J");
}
