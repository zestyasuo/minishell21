/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:39:28 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/12 14:27:12 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_child;

void	interrupt(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (!g_child)
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

void	loop_shell(t_mini *shell, t_list *envp)
{
	char	*input;

	if (!envp)
		return ;
	while (1)
	{
		if (!read_input(&input, shell, envp))
			continue ;
		shell->args = get_args(parse_args(input));
		if (!shell->args)
		{
			ft_lstclear(&shell->args, clear_content);
			print_error("Bad syntax.\n");
			free(input);
			continue ;
		}
		set_variables(shell, envp);
		expand_variables(shell);
		ft_lstiter(shell->args, remove_quotes);
		g_child = 1;
		action_branch(shell, envp);
		g_child = 0;
		ft_lstclear(&shell->args, clear_content);
		free(input);
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
	g_child = 0;
	loop_shell(shell, ft_arrdup_to_lst(envp));
	unset_shell_atrr();
	return (0);
}
