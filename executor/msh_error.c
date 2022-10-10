/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:43:26 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/10 20:15:10 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_print_errno(char *cmd_str, int *fd)
{
	char	*errno_str;

	errno_str = strerror(errno);
	ft_putstr_fd("minishell : ", fd[STD_ERROR]);
	ft_putstr_fd(cmd_str, fd[STD_ERROR]);
	ft_putstr_fd(": ", fd[STD_ERROR]);
	ft_putstr_fd(errno_str, fd[STD_ERROR]);
	ft_putstr_fd("\n", fd[STD_ERROR]);
	return (-1);
}

int	msh_print_error_str(char *cmd_str, char *error_str, int *fd)
{
	ft_putstr_fd("minishell : ", fd[STD_ERROR]);
	ft_putstr_fd(cmd_str, fd[STD_ERROR]);
	ft_putstr_fd(": ", fd[STD_ERROR]);
	ft_putstr_fd(error_str, fd[STD_ERROR]);
	ft_putstr_fd("\n", fd[STD_ERROR]);
	return (-1);
}

void	msh_error_parse(char *str)
{
	if (str == NULL)
		ft_putstr_fd("minishell: syntax error near unexpected token \
														'newline'\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
}
