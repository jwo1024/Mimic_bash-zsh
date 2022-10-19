/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:00:14 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/20 00:38:17 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "msh_error.h"
#include "libft.h"

int	do_pwd(int *fd)
{
	char	*str;
	int		errno;

	str = getcwd(NULL, 0);
	if (str == NULL)
		exit (msh_print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	ft_putstr_fd(str, fd[STD_OUT]);
	ft_putstr_fd("\n", fd[STD_OUT]);
	free(str);
	return (0);
}
