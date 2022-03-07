/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:39:28 by zyasuo            #+#    #+#             */
/*   Updated: 2022/03/07 22:50:04 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
	char	input[1024];

	(void) argv;
	if (argc > 1)
		return (0 * ft_printf(ARGERROR));
	clear();
	ft_printf("Welcome to Minishell!\n");
	while (1)
	{
		if (!read_input(input))
			continue ;
		exec_input(input);
	}
}
