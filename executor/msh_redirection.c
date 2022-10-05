/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:14:37 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/05 22:53:20 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_redirection(t_node *redirct_nd, int *fd)
{
	if (fd == NULL)
		return (-1); // fd 
	msh_set_redirection(redirct_nd, fd);
	if (fd[STD_IN] != STD_IN && dup2(fd[STD_IN], STD_IN) == -1)
		return (-1); // free fds
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
	// 만약 open에 실패 하였을때 오류 처리... ?
	// error "bash: a.txt: Permission denied" // a.txt = redirct_nd->str2
	// std_error 추가하기
	int	std;

	if (ft_strncmp(redirct_nd->str1, "<", 2) == 0) // 입력 리다이렉션
	{
		std = fd[STD_IN];
	
	}
	else if (ft_strncmp(redirct_nd->str1, ">", 2) == 0) // 출력
	{
		std = fd[STD_OUT];

	}
	else if (ft_strncmp(redirct_nd->str1, ">>", 2) == 0) // 출력 붙여쓰기
	{
		std = fd[STD_OUT];
		// 2>> a.txt
	}
	else if (ft_strncmp(redirct_nd->str1, "<<", 2) == 0)
		return (1); // here doc.. 이거는 여기가 아니라 저 저 저어기 tokenzier에서 처리하는게 더 낫지 않나? 근데 ls 를 word로 처리한다. . . . . 
	else
		return (-1);

	if (fd[std] > 2)
			close (fd[std]);
	if (std == STD_OUT)
		fd[std] = open(redirct_nd->str2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (std == STD_IN)
		fd[std] = open(redirct_nd->str2, O_RDONLY);
	if (fd[std] == -1)
		msh_print_errno(redirct_nd->str2);
	return (1);
}



int	*msh_init_fd(void) // init fd
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 3);
	if (fd == NULL)
		msh_print_errno("malloc error");
	fd[0] = STD_IN;
	fd[1] = STD_OUT;
	fd[2] = STD_ERROR;
	return (fd);
}





int	*msh_nopipe_builtin_redirection(t_node *redirct_nd) // 이걸 일반적으로 만들고 
{
	int	*fd;
	
	fd = ft_calloc(2, sizeof(int));
	while (redirct_nd)
	{
	//	fprintf(stderr, "aaa\n");
		if (msh_set_redirection_open(redirct_nd, fd) == -1)
		{
			free(fd);
			return (NULL);
		}
		redirct_nd = redirct_nd->right;
	}
	return (fd);
}
