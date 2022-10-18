/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:43:40 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 20:01:14 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

int	do_exit(char **word, int *fd)
{
	int		j;

	if (word[1] == NULL)
		exit(0);
	j = 0;
	if (word[1][0] == '\0')
		print_errmsg_at_exit(fd, word[1]);
	while (word[1][j] != '\0')
	{
		if (ft_isdigit(word[1][j]) == 0)
			print_errmsg_at_exit(fd, word[1]);
		j++;
	}
	j = 0;
	if (word[2] != NULL)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", fd[STD_ERROR]);
		return (1);
	}
	j = ft_atoi(word[1]);
	exit(j % 256);
}

void	print_errmsg_at_exit(int *fd, char *copy_str)
{
	ft_putstr_fd("bash: exit: ", fd[STD_ERROR]);
	ft_putstr_fd(copy_str, fd[STD_ERROR]);
	ft_putstr_fd(": numeric argument required\n", fd[STD_ERROR]);
	exit(255);
}
