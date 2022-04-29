/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyasuo <zyasuo@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:23:32 by zyasuo            #+#    #+#             */
/*   Updated: 2022/04/26 16:01:15 by zyasuo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_quotestr(char *str, char del)
{
	int		i;
	char	*res;
	int		found;

	i = 1;
	found = 0;
	res = NULL;
	while (str[i])
	{
		if (str[i] == del)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found)
		res = ft_substr(str, 0, i + 1);
	return (res);
}

char	*get_space_str(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && !isspace(str[i]) && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '|')
		i++;
	res = ft_substr(str, 0, i);
	return (res);
}

void	remove_backslash(void *p)
{
	char	*src;
	char	*dst;
	char	garbage;

	garbage = '\\';
	src = (char *)p;
	dst = src;
	while (*src)
	{
		*dst = *src;
		if (*dst != garbage)
			dst++;
		src++;
	}
	*dst = '\0';
}

int	add_arg(t_list **list, char *arg)
{
	int	len;

	if (!arg)
		return (1);
	ft_lstadd_back(list, ft_lstnew(arg));
	len = ft_strlen((char *)ft_lstlast(*list)->content);
	return (len);
}

t_list	*parse_args(char *input)
{
	t_list	*args;
	int		i;
	char	*new_string;

	i = 0;
	args = 0;
	while (input[i])
	{
		while (isspace(input[i]) && input[i])
			i++;
		if (input[i] == '\"' || input[i] == '\'')
		{
			new_string = get_quotestr((input + i), input[i]);
			if (new_string)
				i += add_arg(&args, new_string);
			else
				i += ft_strlen(&input[i]);
		}
		if (input[i] == '|')
			i += add_arg(&args, ft_substr(input, i, 1));
		else if (input[i])
			i += add_arg(&args, get_space_str(input + i));
	}
	ft_lstiter(args, &remove_backslash);
	return (args);
}

// void	remove_backslash(void *p)
// {
// 	char	*src;
// 	int		i;

// 	src = (char *)p;
// 	i = 0;
// 	while (src[i])
// 	{
// 		if (src[i] == '\\')
// 			ft_memmove(&src[i], &src[i + 1], ft_strlen(src) - i);
// 		i++;
// 	}
// }
