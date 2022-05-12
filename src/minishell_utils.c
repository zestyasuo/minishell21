/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:46:47 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/12 22:09:16 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *error)
{
	write(2, error, ft_strlen(error));
}

void	exec_input(char **input, t_list *envp)
{
	int	i;

	i = 0;
	if (!ft_strcmp("pwd", input[0]))
		mini_pwd();
	else if (!ft_strcmp("clear", input[0]))
		mini_clear();
	else if (!ft_strcmp("echo", input[0]))
		mini_echo(input);
	else if (!ft_strcmp("env", input[0]))
		mini_env(envp, "");
	else if (!ft_strcmp("export", input[0]) && !input[1])
		mini_env(envp, "declare -x ");
	else if (!ft_strcmp("exit", input[0]) || !ft_strcmp("export", input[0])
		|| !ft_strcmp("unset", input[0]) || !ft_strcmp("cd", input[0]))
		i = 1;
	else
		return ;
	free_arr(input);
	ft_lstclear(&envp, free);
	exit(i);
}

void	set_shell_attr(void)
{
	struct termios		termios_p;

	tcgetattr(0, &termios_p);
	termios_p.c_cc[VQUIT] = 0;
	termios_p.c_cc[VINTR] = 3;
	if (tcsetattr(0, TCSANOW, &termios_p) == -1)
		perror("set attr");
}

void	unset_shell_atrr(void)
{
	static struct termios	termios_p;

	if (termios_p.c_cflag == 0)
	{
		if (tcgetattr(0, &termios_p) == -1)
			perror("tcgetattr");
	}
	else
	{
		if (tcsetattr(0, TCSANOW, &termios_p) == -1)
			perror("tcunsetattr");
	}
}
