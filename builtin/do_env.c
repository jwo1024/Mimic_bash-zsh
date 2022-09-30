/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:04:58 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/29 16:00:25 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_env(t_list *env_list, int fd)
{
	t_list	*curr;

	curr = env_list;
	while (curr->next != NULL)
	{
		if (find_equal(curr->content))
		{
			ft_putstr_fd((char *)(curr->content), fd);
			ft_putstr_fd("\n", fd);
			curr = curr->next;
		}
	}
	if (find_equal(curr->content))
	{
		ft_putstr_fd((char *)(curr->content), fd);
		ft_putstr_fd("\n", fd);
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
