/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnathali <mnathali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:06:03 by zyasuo            #+#    #+#             */
/*   Updated: 2022/05/15 04:36:42 by mnathali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*transverse_quotes(char	*p, char *str)
{
	char	*p_1;
	char	c;

	c = *(ft_strchr(p, '=') + 1);
	p_1 = p - 1;
	while ((ft_isalpha(*p_1) || ft_isdigit(*p_1)) && p_1 != str)
		p_1--;
	if ((p_1 != str || (p_1 == str && (!ft_isalpha(*str)
		&& !ft_isdigit(*str)))) && *p_1 != ' ')
		return (p + 1);
	p_1 = p;
	while (*p_1 != ' ' && p_1 != str)
	{
		*(p_1 + 1) = *p_1;
		p_1 = p_1 - 1;
	}
	if (p_1 == str)
	{
		*(p_1 + 1) = *p_1;
		*p_1 = c;
	}
	else
		*(p_1 + 1) = c;
	return (p + 2);
}

void	quotes_after_equal(char *str)
{
	char	*p;

	p = str;
	while (p && *p)
	{
		if (*p == '=' && (*(p + 1) == '"' || *(p + 1) == '\'')
			&& p != str && *(p - 1) != ' ')
			break ;
		p++;
	}
	if (!*p)
		return ;
	p = transverse_quotes(p, str);
	if (ft_strchr(p, '=') && (*(ft_strchr(p, '=') + 1) == '"'
		|| *(ft_strchr(p, '=') + 1) == '\''))
		quotes_after_equal(p);
}

int	read_input(char **input, t_mini *shell, t_list *envp)
{
	char	*buf;
	int		input_len;

	buf = readline(SHELLNAME);
	if (!buf)
		shell_exit(shell, envp);
	input_len = ft_strlen(buf);
	if (!input_len)
		return (0);
	*input = malloc(input_len + 1);
	if (!input)
		shell_exit(shell, envp);
	if (input_len)
	{
		add_history(buf);
		ft_strlcpy(*input, buf, ft_strlen(buf) + 1);
		quotes_after_equal(*input);printf("%s\n", *input);
		return (1);
	}
	return (0);
}
