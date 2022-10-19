/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 02:09:52 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/19 12:34:38 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

int	check_dup(char *str, char *env)
{
	int	j;

	j = 0;
	if (str[j] == env[j])
	{
		while (str[j] != '=' && str[j] != '\0')
		{
			j++;
			if (str[j] != env[j])
				break ;
		}
		if (str[j] == '\0' && env[j] == '=')
			return (2);
		if ((str[j] == '=' && env[j] == '=') || \
		(str[j] == '\0' && env[j] == '\0') || (str[j] == '=' && env[j] == '\0'))
			return (1);
	}
	return (0);
}

int	error_print_export(char *str, char *word, int *fd)
{
	ft_putstr_fd("minishell: export: ", fd[STD_ERROR]);
	ft_putstr_fd("`", fd[STD_ERROR]);
	ft_putstr_fd(word, fd[STD_ERROR]);
	ft_putstr_fd("\'", fd[STD_ERROR]);
	ft_putstr_fd(str, fd[STD_ERROR]);
	ft_putstr_fd("\n", fd[STD_ERROR]);
	return (1);
}
