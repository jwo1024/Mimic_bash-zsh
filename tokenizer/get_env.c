/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/23 00:00:23 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **env_list)
{
	char	**list;
	int		i;

	i = 0;
	while (env_list[i])
		i++;
	list = malloc(sizeof(char *) * (i + 1));
	if (list == NULL)
		return (NULL);
	i = 0;
	while (env_list[i])
	{
		list[i] = ft_strdup(env_list[i]);
		i++;
	}
	list[i] = NULL;
	return (list);
}
