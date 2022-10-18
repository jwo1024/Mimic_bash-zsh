/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 16:56:49 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

char	**get_env(char **envp)
{
	char	**list;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	list = malloc_env(i + 2);
	i = 1;
	list[0] = safe_ft_strdup("0", "get_env");
	if (ft_isdigit(envp[0][0]))
		j++;
	while (envp[j])
	{
		if (ft_strncmp("OLDPWD=", envp[j], 7) == 0)
			list[i] = safe_ft_strdup("OLDPWD", "get_env");
		else
			list[i] = safe_ft_strdup(envp[j], "get_env");
		i++;
		j++;
	}
	list[i] = NULL;
	return (list);
}

char	*get_env_to_str(char *env)
{
	t_index	i;

	i.i = -1;
	i.j = 0;
	if (env == NULL)
		return (NULL);
	if (env[0] == '?' && env[1] == '\0')
		return (free_ret(env, g_envp_list[0]));
	while (g_envp_list[++i.i] != NULL)
	{
		if (env[0] == g_envp_list[i.i][0])
		{
			while (env[i.j] != '\0' && g_envp_list[i.i][i.j] \
			!= '\0' && g_envp_list[i.i][i.j] != '=')
			{
				if (env[i.j] != g_envp_list[i.i][i.j])
					break ;
				i.j++;
			}
			if (env[i.j] == '\0' && g_envp_list[i.i][i.j] == '=')
				return (free_ret(env, &g_envp_list[i.i][++i.j]));
		}
		i.j = 0;
	}
	return (free_ret(env, NULL));
}

char	*get_env_at_tokenizer(char *s)
{
	int		i;
	int		double_flag;
	char	*str;

	i = 0;
	double_flag = 0;
	str = safe_ft_strdup(s, "get_env");
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_flag = check_double_flag(&str[i], double_flag);
		if (str[i] == '\'' && double_flag == 0)
			i += skip_dquot(&str[i]);
		if (str[i] == '$')
		{
			str = get_merged_str(str, i);
			if (str == NULL)
				break ;
			i = 0;
		}
		else
			i++;
	}
	return (fix_dol(str));
}

char	*get_merged_str(char *str, int i)
{
	char	*env;

	if (check_next_dol(str[i + 1]))
		str[i] = -3;
	else
	{
		str[i] = -2;
		env = get_env_to_str(get_env_name(&str[i + 1]));
		str = get_merged_env_str(str, env);
	}
	return (str);
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
		front = safe_ft_substr(s, 0, i, "get_env");
	else
		front = NULL;
	if (s[get_env_name_size(&s[i + 1]) + i + 1] != '\0')
		rear = safe_ft_strdup(&s[get_env_name_size(&s[i + 1]) \
		+ i + 1], "get_env");
	else
		rear = NULL;
	merge1 = ft_strjoin_check_null(front, env);
	merge2 = ft_strjoin_check_null(merge1, rear);
	free(s);
	return (merge2);
}
