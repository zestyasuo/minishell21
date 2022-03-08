/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:39:28 by zyasuo            #+#    #+#             */
/*   Updated: 2022/03/08 23:08:47 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	arrayclr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	main(int argc, char **argv)
{
	char	input[MAXARGLEN];
	char	**parsed_args;

	(void) argv;
	if (argc > 1)
		return (0 * ft_printf(ARGERROR));
	clear();
	ft_printf("Welcome to Minishell!\n");
	while (1)
	{
		if (!read_input(input))
			continue ;
		parsed_args = ft_split(input, ' ');
		exec_input(parsed_args);
	}
	arrayclr(parsed_args);
}
