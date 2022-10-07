/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:43:26 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/07 15:59:43 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_print_errno(char *cmd_str, int *fd)
{
	char	*errno_str;

	errno_str = strerror(errno);
//	fprintf(stderr, "minishell: %s: %s\n", str, strerror(errno), errno);
	write(fd[STD_ERROR], "minishell: ", 11);
	write(fd[STD_ERROR], cmd_str, ft_strlen(cmd_str));
	write(fd[STD_ERROR], ": ", fd[STD_ERROR]);
	write(fd[STD_ERROR], errno_str, ft_strlen(errno_str));
	write(fd[STD_ERROR], "\n", 1);

	// ft_strjoin?
//	free(errno_str);
	return (-1);
}

int	msh_print_error_str(char *cmd_str, char *error_str, int *fd)
{
	write(fd[STD_ERROR], "minishell: ", 11);
	write(fd[STD_ERROR], cmd_str, ft_strlen(cmd_str));
	write(fd[STD_ERROR], ": ", 2);
	write(fd[STD_ERROR], error_str, ft_strlen(error_str));
	write(fd[STD_ERROR], "\n", 1);

	return (-1);
}