/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:00:14 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/15 16:21:38 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(int *fd)
{
	char	*str;
	int		errno;

	str = getcwd(NULL, 0);
	if (str == NULL)
	{
	//	msh_print_error_str("pwd", NULL, strerror(errno), fd);
		return (msh_print_errno(fd[STD_ERROR], "pwd", NULL, -1)); // rtn 2? 
	}
	ft_putstr_fd(str, fd[STD_OUT]);
	ft_putstr_fd("\n", fd[STD_OUT]);
	free(str);
	return (0);
}
