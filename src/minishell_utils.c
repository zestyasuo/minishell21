/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:46:47 by zyasuo            #+#    #+#             */
/*   Updated: 2022/03/07 22:50:10 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear(void)
{
	ft_printf("\033[H\033[J");
}

int	read_input(char *input)
{
	char	*buf;

	buf = readline(">>>");
	if (ft_strlen(buf))
	{
		add_history(buf);
		ft_strlcpy(input, buf, ft_strlen(buf) + 1);
		return (1);
	}
	return (0);
}

void	pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}

void	exec_input(char *input)
{

	if (!ft_strncmp("pwd", input, 3))
		pwd();
	if (!ft_strncmp("exit", input, 4))
		exit(0);
}
