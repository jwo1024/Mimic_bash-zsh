/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:11:29 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 17:55:51 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_unset(char **word, int *fd)
{
	t_index	*idx;

	idx = make_idx();
	idx->k = 1;
	while (word[idx->k] != NULL)
	{
		check_export_word(word[idx->k], fd);
		while (g_envp_list[idx->i] != NULL)
		{
			if (check_unset_dup(word[idx->k], g_envp_list[idx->i]))
				unset_env(idx);
			idx->i++;
		}
		idx->i = 0;
		idx->k++;
	}
	free(idx);
	return (0);
}

void	unset_env(t_index *idx)
{
	free(g_envp_list[idx->i]);
	while (g_envp_list[idx->i + 1] != NULL)
	{
		g_envp_list[idx->i] = g_envp_list[idx->i + 1];
		idx->i++;
	}
	g_envp_list[idx->i] = g_envp_list[idx->i + 1];
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
