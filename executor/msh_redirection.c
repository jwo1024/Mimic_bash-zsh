/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:14:37 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/10 13:22:37 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_redirection(t_node *redirct_nd, int *fd) // msh_apply_redirection
{
	if (fd == NULL)
		return (-1);
	if (msh_set_redirection(redirct_nd, fd) == NULL)
		return (-1);
	if (fd[STD_IN] != STD_IN && dup2(fd[STD_IN], STD_IN) == -1)
		return (-1); // free fds   msh_print_errno("fail dup fd", fd) 해줄까 말까..
	if (fd[STD_OUT] != STD_OUT && dup2(fd[STD_OUT], STD_OUT) == -1)
		return (-1);
	if (fd[STD_ERROR] != STD_ERROR && dup2(fd[STD_ERROR], STD_ERROR) == -1)
		return (-1);
	return (1);
}

int	*msh_set_redirection(t_node *redirct_nd, int *fd)
{
	while (redirct_nd)
	{
		if (msh_set_redirection_open(redirct_nd, fd) == -1)
			return (NULL);
		redirct_nd = redirct_nd->right;
	}
	return (fd);
}

int	msh_set_redirection_open(t_node *redirct_nd, int *fd)
{
	if (ft_strncmp(redirct_nd->str1, "<", 2) == 0)
	{
		if (fd[STD_IN] > 2)
			close (fd[STD_IN]);
		fd[STD_IN] = open(redirct_nd->str2, O_RDONLY);
		if (fd[STD_IN] == -1)
			return (msh_print_errno(redirct_nd->str2, fd));
	}
	else if (ft_strncmp(redirct_nd->str1, ">", 2) == 0)
	{
		if (fd[STD_OUT] > 2)
			close (fd[STD_OUT]);
		fd[STD_OUT]= open(redirct_nd->str2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[STD_OUT] == -1)
			return (msh_print_errno(redirct_nd->str2, fd));
	}
	else if (ft_strncmp(redirct_nd->str1, ">>", 3) == 0)
	{
		if (fd[STD_OUT] > 2)
			close (fd[STD_OUT]);
		fd[STD_OUT] = open(redirct_nd->str2, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[STD_OUT] == -1)
			return (msh_print_errno(redirct_nd->str2, fd));
	}
	else if (ft_strncmp(redirct_nd->str1, "<<", 3) == 0)
		; // here doc.. 이거는 여기가 아니라 저 저 저어기 tokenzier에서 처리하는게 더 낫지 않나? 근데 ls 를 word로 처리한다. . . . . 
	else
		return (-1);
	return (1);
}

int	*msh_init_fd(void) // init fd
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 3);
	if (fd == NULL)
		return (NULL); //msh_print_errno("malloc error", fd); ?
	fd[0] = STD_IN;
	fd[1] = STD_OUT;
	fd[2] = STD_ERROR;
	return (fd);
}
