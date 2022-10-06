/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:11:29 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 21:49:23 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_unset(char *word, int fd)
{
	int		i;
	char	*str;

	i = 0;
	(void)fd;
	str = ft_strdup(&word[6]);
	while (g_envp_list[i] != NULL)
	{
		if (check_unset_dup(str, g_envp_list[i]))
		{
			free(g_envp_list[i]);
			while (g_envp_list[i + 1] != NULL)
			{
				g_envp_list[i] = g_envp_list[i + 1];
				i++;
			}
			g_envp_list[i] = g_envp_list[i + 1];
		}
		i++;
	}
	return (1);
}

int	check_unset_dup(char *str, char *env)
{
	int	j;

	j = 0;
	if (str[j] == env[j])
	{
		while (str[j] != '\0')
		{
			j++;
			if (str[j] != env[j])
				break ;
		}
		if (str[j] == '\0' && (env[j] == '=' || env[j] == '\0'))
			return (1);
	}
	return (0);
}
