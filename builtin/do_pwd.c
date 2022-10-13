/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:00:14 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 22:02:53 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// 오류처리는 안함.... 다음에 알아보자
int	do_pwd(int *fd)
{
	char	*str;
	int		errno;

	str = getcwd(NULL, 0);
	if (str == NULL)
	{
		msh_print_error_str("pwd", NULL, strerror(errno), fd);
		return (-1);
	}
	ft_putstr_fd(str, fd[STD_OUT]);
	ft_putstr_fd("\n", fd[STD_OUT]);
	free(str);
	return (0);
}
