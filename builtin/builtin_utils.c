/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:52:32 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/15 00:29:57 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

t_index	*make_idx(void)
{
	t_index	*new;

	new = malloc(sizeof(t_index));
	if (new == NULL)
	{
		ft_putstr_fd("malloc Error\n", STD_ERROR);
		exit(1);
	}
	new->i = 0;
	new->j = 0;
	new->k = 0;
	return (new);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**malloc_env(int size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * size);
	if (new == NULL)
	{
		ft_putstr_fd("malloc Error\n", STD_ERROR);
		exit(1);
	}
	while (i != size)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}
