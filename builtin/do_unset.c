/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:11:29 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 18:14:53 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_unset(char *word, char **env_list, int fd)
{
	int	i;

	i = -1;
	while (env_list[++i] != NULL)
	{
		if (check_dup(word, env_list[i]))
		{

		}
	}
	return (1);
}
