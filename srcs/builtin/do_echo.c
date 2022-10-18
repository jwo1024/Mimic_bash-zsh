/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:21:27 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 19:56:58 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "tokenizer.h"
#include "libft.h"

int	do_echo(char **word, int *fd)
{
	int		opt;
	int		i;

	if (word[1] == NULL)
	{
		ft_putstr_fd("\n", fd[STD_OUT]);
		return (1);
	}
	opt = check_opt(word);
	i = opt;
	while (word[i] != NULL)
	{
		ft_putstr_fd(word[i], fd[STD_OUT]);
		if (word[i + 1] != NULL)
			ft_putchar_fd(' ', fd[STD_OUT]);
		i++;
	}
	if (opt == 1)
		ft_putstr_fd("\n", fd[STD_OUT]);
	return (0);
}

int	check_opt(char **s)
{
	int		count;
	int		count_n;

	count = 1;
	count_n = 2;
	while (ft_strncmp("-n", s[count], 2) == 0)
	{
		while (s[count][count_n] == 'n')
			count_n++;
		if (s[count][count_n] != '\0')
			break ;
		count++;
		count_n = 2;
		if (s[count] == NULL)
			break ;
	}
	return (count);
}

int	check_dequot(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0')
				if (s[i++] == '\"')
					return (1);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0')
				if (s[i++] == '\'')
					return (1);
		}
		else
			i++;
	}
	return (0);
}
