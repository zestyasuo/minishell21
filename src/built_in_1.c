/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:50:05 by zyasuo            #+#    #+#             */
/*   Updated: 2022/03/08 23:16:30 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}

void	cd(char **path)
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
}

void	clear(void)
{
	ft_printf("\033[H\033[J");
}
