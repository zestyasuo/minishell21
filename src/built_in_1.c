/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:50:05 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/09 13:00:26 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_pwd(void)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	ft_printf("%s\n", buf);
}

int	mini_cd(char **path, char **envp)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i > 2 && envp)
		print_error("Too many arguments\n");
	else if (!chdir(path[1]))
		return (0);
	if (envp)
		perror("cd ");
	return (1);
}

void	mini_echo(char **args)
{
	int		i;
	int		endl;

	if (!args[1])
	{
		write(1, "\n", 1);
		return ;
	}
	endl = !ft_strncmp("-n", args[1], ft_strlen(args[1]));
	if (!args[2] && endl)
		return ;
	i = 1 + endl;
	while (args[i + 1])
		ft_printf("%s ", args[i++]);
	ft_printf("%s", args[i]);
	if (!endl)
		write(1, "\n", 1);
}

int	shell_exit(t_mini *shell, t_list *envp)
{
	int		i;
	int		code;
	char	*str;

	i = 0;
	code = 1;
	str = 0;
	if (((t_list *)(shell->args->content))->next)
		str = ((t_list *)(shell->args->content))->next->content;
	while (str && str[i] && code == 1)
	{
		if (!ft_isdigit(str[i]))
			code = 2;
		i++;
	}
	if (ft_lstsize(shell->args->content) > 2 && code == 1)
		return (0 * printf("mshell: exit: too many arguments\n") + 1);
	if (code == 1 && str)
		code = ft_atoi(str);
	ft_lstclear(&shell->var_list, destroy_var);
	ft_lstclear(&shell->args, clear_content);
	ft_lstclear(&envp, free);
	free(shell);
	write(1, "exit\n", 5);
	exit(code);
}

void	mini_clear(void)
{
	ft_printf("\033[H\033[J");
}
