/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:50:05 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/05 15:28:02 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}

void	mini_cd(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i > 2)
		print_error("Too many arguments");
	if (!chdir(path[1]))
		return ;
	perror("cd ");
	if (path)
		free(path);
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

void	shell_exit(int code)
{
	write(1, "exit\n", 5);
	exit(code);
}

void	mini_clear(void)
{
	ft_printf("\033[H\033[J");
}
