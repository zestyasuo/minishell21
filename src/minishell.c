/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:39:28 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/07 00:08:33 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	interrupt(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	loop_shell(t_mini *shell, char **envp)
{
	char			*input;
	
	while (1)
	{
		if (!read_input(&input))
			continue ;
		shell->args = get_args(parse_args(input));
		if (!shell->args)
		{
			ft_lstclear(&shell->args, clear_content);
			print_error("Bad syntax.\n");
			free(input);
			continue ;
		}
		expand_variables(shell);
		//print_args(shell->args->content);
		//ft_lstiter(shell->args, print_args);
		//second_parser(shell);
		action_branch(shell, envp);//////////////////////////////////
		ft_lstclear(&shell->args, clear_content);
		free(input);
		check_returned_value(shell->var_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				*shell;
	struct sigaction	sa;
	struct termios		termios_p;

	(void) argv;
	tcgetattr(0, &termios_p);
	termios_p.c_lflag &= ~(ISIG);//видимо при такой инициализации нет возможности посылать сигналы запускаемым из минишелла процессам
	termios_p.c_cc[VQUIT] = 0;
	termios_p.c_cc[VINTR] = 3;
	tcsetattr(0, 0, &termios_p);
	sa.sa_handler = &interrupt;
	sigaction(SIGINT, &sa, NULL);
	if (argc > 1)
		return (0 * ft_printf(ARGERROR));
	if (create_shell(&shell, envp))
		return (1);
	loop_shell(shell, envp);
	return (0);
}

		// if (!shell->args)
		// 	return (ft_printf("Failed to read args\n"));
		// if (input[0] == '/' || input[0] == '.')
		// 	exec_child(shell->args, envp);
		// else
		// 	exec_input(shell->args, envp);
		// array_clear(shell->args);