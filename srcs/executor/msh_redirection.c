/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:14:37 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 19:50:07 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "msh_error.h"

int	msh_redirection(t_node *redirct_nd, int *fd)
{
	if (fd == NULL || fd[STD_IN] == -1 || fd[STD_OUT] == -1)
		return (-1);
	if (msh_set_redirection(redirct_nd, fd) == NULL)
		return (-1);
	if (fd[STD_IN] != STD_IN && dup2(fd[STD_IN], STD_IN) == -1)
		return (msh_print_errno(STD_ERROR, "fail redirection", NULL, -1));
	if (fd[STD_OUT] != STD_OUT && dup2(fd[STD_OUT], STD_OUT) == -1)
		return (msh_print_errno(STD_ERROR, "fail redirection", NULL, -1));
	if (fd[STD_ERROR] != STD_ERROR && dup2(fd[STD_ERROR], STD_ERROR) == -1)
		return (msh_print_errno(STD_ERROR, "fail redirection", NULL, -1));
	return (1);
}

int	*msh_set_redirection(t_node *redirct_nd, int *fd)
{
	while (redirct_nd)
	{
		if (msh_set_redirection_type(redirct_nd, fd) == -1)
			return (NULL);
		redirct_nd = redirct_nd->left;
	}
	return (fd);
}

int	msh_init_fd(int **fd)
{
	if (fd == NULL || *fd == NULL)
		return (-1);
	(*fd) = ft_calloc(3, sizeof(int));
	if ((*fd) == NULL)
		return (msh_print_errno(STD_ERROR, "fail init fd", NULL, -1));
	(*fd)[0] = STD_IN;
	(*fd)[1] = STD_OUT;
	(*fd)[2] = STD_ERROR;
	return (1);
}
