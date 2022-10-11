/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/11 15:59:51 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

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
	t_index	idx;

	idx.i = -1;
	idx.j = 0;
	if (env_name == NULL)
		return (NULL);
	while (g_envp_list[++idx.i] != NULL)
	{
		if (env_name[0] == g_envp_list[idx.i][0])
		{
			while (env_name[idx.j] != '\0' && g_envp_list[idx.i][idx.j] \
			!= '\0' && g_envp_list[idx.i][idx.j] != '=')
			{
				if (env_name[idx.j] != g_envp_list[idx.i][idx.j])
					break ;
				idx.j++;
			}
			if (env_name[idx.j] == '\0' && g_envp_list[idx.i][idx.j] == '=')
			{
				free(env_name);
				return (ft_strdup(&g_envp_list[idx.i][idx.j + 1]));
			}
		}
		idx.j = 0;
	}
	free(env_name);
	return (NULL);
}

char	*get_env_at_tokenizer(char *s)
{
	t_index	idx;
	char	*env;
	char	*copy_str;

	idx.i = 0;
	idx.j = 0;
	copy_str = ft_strdup(s);
	while (copy_str[idx.i] != '\0')
	{
		if (copy_str[idx.i] == '\'')
			idx.i += skip_dquot(&copy_str[idx.i]);
		if (copy_str[idx.i] == '$')
		{
			copy_str[idx.i] = -2;
			env = get_env_to_str(get_env_name(&copy_str[idx.i + 1]));
			copy_str = get_merged_env_str(copy_str, env);
		}
		idx.i++;
	}
	free(s);
	s = copy_str;
	return (s);
}

char	*get_merged_env_str(char *s, char *env)
{
	int		i;
	char	*front;
	char	*rear;
	char	*merge1;

	i = 0;
	while (s[i] != -2)
		i++;
	front = ft_substr(s, 0, i);
	rear = ft_strdup(&s[get_env_name_size(&s[i + 1]) + i + 1]);
	if (env == NULL)
	{
		merge1 = ft_strjoin(front, rear);
		free(front);
		free(rear);
		return (merge1);
	}
	else
	{
		merge1 = ft_strjoin(front, env);
		free (front);
		free (env);
		front = ft_strjoin(merge1, rear);
		free (rear);
		free (merge1);
		free (s);
	}
	return (front);
}

int	get_env_name_size(char *s)
{
	int		i;

	i = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
		return (i);
	while (s[i] != '\0')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			break ;
		i++;
	}
	return (i);
}

char	*get_env_name(char *s)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = get_env_name_size(s);
	if (i == 0)
		return (NULL);
	name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
	{
		ft_putstr_fd("malloc error\n", STD_ERROR);
		exit(1);
	}
	while (i != 0)
	{
		name[j] = s[j];
		j++;
		i--;
	}
	name[j] = '\0';
	return (name);
}
