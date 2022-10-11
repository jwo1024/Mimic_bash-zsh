/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:11:29 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/12 01:33:53 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_unset(char *word)
{
	t_index	*idx;
	char	*str;
	char	*copystr;

	idx = make_idx();
	copystr = del_dequot(ft_strdup(&word[6]));
	str = ft_strdup(copystr);
	while (copystr[idx->k] != '\0')
	{
		while (copystr[idx->k] != '\0' && copystr[idx->k] != ' ')
			str[idx->j++] = copystr[idx->k++];
		str[idx->j] = '\0';
		while (g_envp_list[idx->i] != NULL)
		{
			if (check_unset_dup(str, g_envp_list[idx->i]))
				unset_env(idx);
			idx->i++;
		}
		if (copystr[idx->k] != '\0')
			idx->k++;
		idx->j = 0;
		idx->i = 0;
	}
	free(copystr);
	free(str);
	free(idx);
	return (1);
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
