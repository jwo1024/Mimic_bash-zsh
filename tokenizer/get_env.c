/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/07 17:27:41 by jaeyjeon         ###   ########.fr       */
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

char	*get_env_to_str(char *env_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_envp_list[i] != NULL)
	{
		if (env_name[0] == g_envp_list[i][0])
		{
			while (env_name[j] != '\0' && g_envp_list[i][j] != '\0' && g_envp_list[i][j] != '=')
			{
				if (env_name[j] != g_envp_list[i][j])
					break ;
				j++;
			}
			if (env_name[j] == '\0' && g_envp_list[i][j] == '=')
				return (ft_strdup(&g_envp_list[i][j + 1]));
		}
		j = 0;
		i++;
	}
	return (NULL);
}
