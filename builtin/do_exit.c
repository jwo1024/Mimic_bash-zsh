/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:43:40 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 00:09:48 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_exit(char *word, int *fd)
{
	char	*copy_str;
	int		i;

	printf("exit: %s\n", word);
//	copy_str = del_dequot(ft_strdup(&word[5]));
	copy_str = word; // 임시
	if (copy_str[0] == '\0')
		exit(0);
	i = 0;
	while (copy_str[i] != '\0' && copy_str[i] != ' ')
	{
		if (ft_isdigit(copy_str[i++]) == 0)
			print_errmsg_at_exit(fd, copy_str);
	}
	i = -1;
	while (copy_str[++i] != '\0')
	{
		if (copy_str[i] == ' ')
		{
			ft_putstr_fd("bash: exit: too many arguments", fd[STD_ERROR]);
			ft_putstr_fd("\n", fd[STD_ERROR]);
			return (1);
		}
	}
	i = ft_atoi(copy_str);
	exit(i % 256);
}

void	print_errmsg_at_exit(int *fd, char *copy_str)
{
	int	i;

	ft_putstr_fd("bash: exit: ", fd[STD_ERROR]);
	i = 0;
	while (copy_str[i] != '\0' && copy_str[i] != ' ')
		write(fd[STD_ERROR], &copy_str[i++], 1);
	ft_putstr_fd(": numeric argument required", fd[STD_ERROR]);
	ft_putstr_fd("\n", fd[STD_ERROR]);
	exit(255);
}
