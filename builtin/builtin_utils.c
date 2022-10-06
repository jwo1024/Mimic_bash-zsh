/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:52:32 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 17:58:04 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

t_index	*make_idx(void)
{
	t_index	*new;

	new = malloc(sizeof(t_index));
	new->i = 0;
	new->j = 0;
	return (new);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (i != 0)
		i--;
	while (i != 0)
	{
		free(env[i]);
		i--;
	}
	free(env[i]);
	free(env);
}

char	**malloc_env(int size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * size);
	while (i != size)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}
