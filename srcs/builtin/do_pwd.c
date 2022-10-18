/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:00:14 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 19:54:14 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_error.h"
#include "libft.h"

int	do_pwd(int *fd)
{
	char	*str;
	int		errno;

	str = getcwd(NULL, 0);
	if (str == NULL)
		return (msh_print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	ft_putstr_fd(str, fd[STD_OUT]);
	ft_putstr_fd("\n", fd[STD_OUT]);
	free(str);
	return (0);
}
