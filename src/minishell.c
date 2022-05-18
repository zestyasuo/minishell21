/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:39:28 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/18 15:11:46 by mnathali         ###   ########.fr       */
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
		g_child = 130;
	}
}

void	set_shell_attr(void)
{
	struct termios		termios_p;
	struct sigaction	sa;

	sa.sa_handler = &interrupt;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	tcgetattr(0, &termios_p);
	termios_p.c_cc[VQUIT] = 0;
	termios_p.c_cc[VINTR] = 3;
	tcsetattr(0, 0, &termios_p);
}

void	silence_signal(int sig)
{
	(void) sig;
	if (sig == SIGQUIT)
		ft_printf("Quit\n");
	else
		write(1, "\n" , 1);
}

void	unset_shell_atrr(void)
{
	static struct termios	termios_p;
	struct sigaction	sa;

	sa.sa_handler = &silence_signal;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
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
		if (g_child == 130)
			change_var_value(shell->var_list, "?", ft_itoa(130));
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
		// ft_lstiter(shell->args, print_args);
		g_child = 0;
		ft_lstclear(&shell->args, clear_content);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				*shell;

	(void) argv;
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
