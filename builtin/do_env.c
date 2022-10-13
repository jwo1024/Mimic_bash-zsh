/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:04:58 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 21:58:02 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(int *fd)
{
	int	i;

	i = 0;
	while (g_envp_list[i] != NULL)
	{
		if (find_equal(g_envp_list[i]))
		{
			ft_putstr_fd(g_envp_list[i], fd[STD_OUT]);
			ft_putstr_fd("\n", fd[STD_OUT]);
		}
		i++;
	}
	return (0);
}

int	find_equal(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
