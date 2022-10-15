/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:14:37 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/16 02:18:05 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (msh_set_redirection_open(redirct_nd, fd) == -1)
			return (NULL);
		redirct_nd = redirct_nd->left;
	}
	return (fd);
}

int	msh_set_redirection_open(t_node *redirct_nd, int *fd)
{
	if (ft_strncmp(redirct_nd->str1, "<", 2) == 0)
	{
		if (fd[STD_IN] > 2)
			close (fd[STD_IN]);
		fd[STD_IN] = open(redirct_nd->str2[0], O_RDONLY);
		if (fd[STD_IN] == -1)
			return (msh_print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, -1));
	}
	else if (ft_strncmp(redirct_nd->str1, ">", 2) == 0)
	{
		if (fd[STD_OUT] > 2)
			close (fd[STD_OUT]);
		fd[STD_OUT] = open(redirct_nd->str2[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[STD_OUT] == -1)
			return (msh_print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, -1));
	}
	else if (ft_strncmp(redirct_nd->str1, ">>", 3) == 0)
	{
		if (fd[STD_OUT] > 2)
			close (fd[STD_OUT]);
		fd[STD_OUT] = open(redirct_nd->str2[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[STD_OUT] == -1)
			return (msh_print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, -1));
	}
	else if (ft_strncmp(redirct_nd->str1, "<<", 3) == 0)
	{
		if (fd[STD_IN] > 2)
			close (fd[STD_IN]);
		fd[STD_IN] = open(redirct_nd->str2[0], O_RDONLY);
		if (fd[STD_IN] == -1)
			return (msh_print_errno(fd[STD_ERROR], redirct_nd->str2[0], NULL, -1));
		unlink(redirct_nd->str2[0]);
	}
	else
		return (-1);
	return (1);
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
