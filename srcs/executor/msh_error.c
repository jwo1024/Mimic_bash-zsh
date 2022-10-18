/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:43:26 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 19:52:20 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "msh_error.h"
#include <sys/errno.h>

int	msh_print_error(int fd, char *str1, char *str2, int rtn)
{
	ft_putstr_fd("minishell: ", fd);
	if (str1 != NULL)
		ft_putstr_fd(str1, fd);
	if (str2 != NULL)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(str2, fd);
	}
	ft_putstr_fd("\n", fd);
	return (rtn);
}

int	msh_print_errno(int fd, char *str1, char *str2, int rtn)
{
	char	*errno_str;

	errno_str = strerror(errno);
	ft_putstr_fd("minishell: ", fd);
	if (str1 != NULL)
	{
		ft_putstr_fd(str1, fd);
		ft_putstr_fd(": ", fd);
	}
	if (str2 != NULL)
	{
		ft_putstr_fd(str2, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_putstr_fd(errno_str, fd);
	ft_putstr_fd("\n", fd);
	return (rtn);
}
