/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:06:03 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/10 20:48:42 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	read_input(char **input)//, t_mini *shell, t_list *envp)
{
	char	*buf;
	int		input_len;

	buf = readline(SHELLNAME);
	if (!buf)
		exit(0 * write(1, "exit\n", 5));
	input_len = ft_strlen(buf);
	if (!input_len)
		return (0);
	*input = malloc(input_len + 1);
	if (!input)
		exit(0 * write(1, "exit\n", 5));
	if (input_len)
	{
		add_history(buf);
		ft_strlcpy(*input, buf, ft_strlen(buf) + 1);
		return (1);
	}
	return (0);
}
