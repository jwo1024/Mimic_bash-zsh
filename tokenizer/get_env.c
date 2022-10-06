/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 17:00:36 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **envp)
{
	char	**list;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	list = malloc_env(i + 1);
	if (list == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		list[i] = ft_strdup(envp[i]);
		i++;
	}
	list[i] = NULL;
	return (list);
}
