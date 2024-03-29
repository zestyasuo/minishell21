/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:06:03 by zyasuo            #+#    #+#             */
/*   Updated: 2022/04/30 00:39:53 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	read_input(char **input)
{
	char	*buf;
	int		input_len;

	buf = readline(SHELLNAME);
	if (!buf)
		shell_exit(0);
	input_len = ft_strlen(buf);
	if (!input_len)
		return (0);
	*input = malloc(input_len + 1);
	if (!input)
		shell_exit(1);
	if (input_len)
	{
		add_history(buf);
		ft_strlcpy(*input, buf, ft_strlen(buf) + 1);
		return (1);
	}
	return (0);
}
