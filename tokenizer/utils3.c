/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:40:20 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/16 02:36:18 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

char	*del_dequot(char **str)
{
	char	*s;
	char	*new_str;
	t_index	*idx;

	s = *str;
	idx = make_idx();
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"')
			do_del_dequot(new_str, s, '\"', idx);
		else if (s[idx->i] == '\'')
			do_del_dequot(new_str, s, '\'', idx);
		else
			new_str[idx->j++] = s[idx->i++];
	}
	new_str[idx->j] = '\0';
	free (s);
	free (idx);
	*str = new_str;
	return (new_str);
}

void	do_del_dequot(char *new_str, char *s, char c, t_index *idx)
{
	if (check_dequot(&s[idx->i]))
	{
		idx->i++;
		while (s[idx->i] != c)
			new_str[idx->j++] = s[idx->i++];
		idx->i++;
	}
	else
		new_str[idx->j++] = s[idx->i++];
}

char	*ft_strjoin_check_null(char *s1, char *s2)
{
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		result = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
		return (result);
	}
	if (s1 == NULL && s2 != NULL)
	{
		result = ft_strdup(s2);
		free(s2);
		return (result);
	}
	if (s1 != NULL && s2 == NULL)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}
	return (NULL);
}

void	change_exit_status(int num)
{
	free(g_envp_list[0]);
	g_envp_list[0] = ft_itoa(num);
}
