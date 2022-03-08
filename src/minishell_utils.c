/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:46:47 by zyasuo            #+#    #+#             */
/*   Updated: 2022/03/08 23:15:13 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(char *error)
{
	write(2, error, ft_strlen(error));
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

void	exec_input(char **input)
{
	if (!ft_strncmp("pwd", input[0], ft_strlen(input[0])))
		pwd();
	else if (!ft_strncmp("exit", input[0], ft_strlen(input[0])))
		exit(0);
	else if (!ft_strncmp("clear", input[0], ft_strlen(input[0])))
		clear();
	else if (!ft_strncmp("cd", input[0], ft_strlen(input[0])))
		cd(input);
	else
		print_error("Such word are beyond my humble comprehension\n");
}
