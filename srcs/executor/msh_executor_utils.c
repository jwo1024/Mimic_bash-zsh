/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:33:07 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/20 01:56:51 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "msh_error.h"
#include "builtin.h"

int	msh_exit_status(int statloc)
{
	if ((statloc & 255) == 0)
		return ((statloc >> 8) & 255);
	return ((statloc & 127) + 128);
}

int	msh_init_fd(int **fd)
{
	if (fd == NULL)
		return (-1);
	(*fd) = safe_ft_calloc(3, sizeof(int), "fail init fd");
	(*fd)[0] = STD_IN;
	(*fd)[1] = STD_OUT;
	(*fd)[2] = STD_ERROR;
	return (1);
}

void	msh_close(int fd)
{
	if (close(fd) == -1)
		msh_print_errno(STD_ERROR, NULL, NULL, 1);
}
