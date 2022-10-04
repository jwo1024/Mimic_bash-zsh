/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/03 18:12:42 by jaeyjeon         ###   ########.fr       */
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
	list = malloc(sizeof(char *) * (i + 1));
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
