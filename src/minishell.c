/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:39:28 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/10 01:43:53 by zyasuo           ###   ########.fr       */
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
	if (sig == SIGQUIT)
		ft_printf("Quit\n");
}

void	set_shell_attr(void)
{
	struct termios		termios_p;

	tcgetattr(0, &termios_p);
	termios_p.c_cc[VQUIT] = 0;
	termios_p.c_cc[VINTR] = 3;
	tcsetattr(0, 0, &termios_p);
}

void	unset_shell_atrr(void)
{
	static struct termios	termios_p;

	if (termios_p.c_cflag == 0)
		tcgetattr(0, &termios_p);
	else
		tcsetattr(0, 0, &termios_p);
}

void	loop_shell(t_mini *shell, char **envp)
{
	char			*input;

	(void)envp;
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
		ft_lstiter(shell->args, remove_quotes);
		// ft_lstiter(shell->args, print_args);
		unset_shell_atrr();
		action_branch(shell, envp);
		set_shell_attr();
		ft_lstclear(&shell->args, clear_content);
		free(input);
		check_returned_value(shell->var_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				*shell;
	struct sigaction	sa;

	(void) argv;
	sa.sa_handler = &interrupt;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (argc > 1)
		return (0 * ft_printf(ARGERROR));
	if (create_shell(&shell, envp))
		return (1);
	unset_shell_atrr();
	set_shell_attr();
	loop_shell(shell, envp);
	unset_shell_atrr();
	return (0);
}

		// if (!shell->args)
		// 	return (ft_printf("Failed to read args\n"));
		// if (input[0] == '/' || input[0] == '.')
		// 	exec_child(shell->args, envp);
		// else
		// 	exec_input(shell->args, envp);
		// array_clear(shell->args);