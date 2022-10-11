/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:21:27 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/11 01:43:30 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_echo(char *word, int *fd)
{
	char	*copy_str;
	int		opt;

	opt = 0;
	copy_str = ft_strdup(&word[5]);
	while (check_opt(&copy_str[opt]) != 0)
		opt += check_opt(&copy_str[opt]);
	ft_putstr_fd(&copy_str[opt], fd[STD_OUT]);
	if (opt == 0 && copy_str[opt] != '\0')
		ft_putstr_fd("\n", fd[STD_OUT]);
	free (copy_str);
	return (0);
}

int	check_opt(char *s)
{
	int	count;

	count = 0;
	if (ft_strncmp("-n", s, 2) != 0)
		return (0);
	else
	{
		count = 2;
		while (s[count] != '\0')
		{
			if (s[count] == 'n')
				count++;
			else if (s[count] == ' ')
			{
				count++;
				break ;
			}
			else
				return (0);
		}
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
