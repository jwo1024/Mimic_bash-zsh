/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:04:58 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/03 20:31:51 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(char **env_list, int fd)
{
	int	i;

	i = 0;
	while (env_list[i] != NULL)
	{
		if (find_equal(env_list[i]))
		{
			ft_putstr_fd(env_list[i], fd);
			ft_putstr_fd("\n", fd);
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
