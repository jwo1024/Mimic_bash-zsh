/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/15 20:42:48 by jaeyjeon         ###   ########.fr       */
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

char	*get_env_to_str(char *env_name, int exit_status)
{
	t_index	idx;

	idx.i = -1;
	idx.j = 0;
	if (env_name == NULL)
		return (NULL);
	if (env_name[0] == '?' && env_name[1] == '\0')
	{
		free(env_name);
		return (ft_itoa(exit_status));
	}
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

int	check_double_flag(char *s, int double_flag)
{
	if (double_flag == 1)
		double_flag = 0;
	else if (skip_dquot(s) != 1 && double_flag == 0)
		double_flag = 1;
	return (double_flag);
}

char	*get_env_at_tokenizer(char *s, int exit)
{
	int		i;
	int		double_flag;
	char	*env;
	char	*str;

	i = 0;
	double_flag = 0;
	str = ft_strdup(s);
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_flag = check_double_flag(&str[i], double_flag);
		if (str[i] == '\'' && double_flag == 0)
			i += skip_dquot(&str[i]);
		if (str[i] == '$')
		{
			if (check_next_dol(str[i + 1]))
				str[i] = -3;
			else
			{
				str[i] = -2;
				env = get_env_to_str(get_env_name(&str[i + 1]), exit);
				str = get_merged_env_str(str, env);
				if (str == NULL)
					break ;
			}
			i = 0;
		}
		else
			i++;
	}
	fix_dol(str);
	return (str);
}

void	fix_dol(char *str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != '\0')
		if (str[i] == -3)
			str[i] = '$';
}

int	check_next_dol(char c)
{
	if (c == '?')
		return (0);
	if (!(ft_isalnum(c) || c == '_'))
		return (1);
	return (0);
}

char	*get_merged_env_str(char *s, char *env)
{
	int		i;
	char	*front;
	char	*rear;
	char	*merge1;
	char	*merge2;

	i = 0;
	while (s[i] != -2)
		i++;
	if (i != 0)
		front = ft_substr(s, 0, i);
	else
		front = NULL;
	if (s[get_env_name_size(&s[i + 1]) + i + 1] != '\0')
		rear = ft_strdup(&s[get_env_name_size(&s[i + 1]) + i + 1]);
	else
		rear = NULL;
	merge1 = ft_strjoin_check_null(front, env);
	merge2 = ft_strjoin_check_null(merge1, rear);
	free(s);
	return (merge2);
}
