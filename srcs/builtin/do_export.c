/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:52:20 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/20 00:39:19 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "libft.h"

int	do_export(char **word, int *fd)
{
	int		i;
	int		return_value;
	int		save_value;

	i = 1;
	return_value = 0;
	save_value = 0;
	if (word[1] == NULL || word[1][0] == '\0')
		print_env(fd);
	while (word[i] != NULL)
	{
		return_value += check_export_word(word[i], fd);
		if (return_value != save_value)
			;
		else
			g_envp_list = change_env(safe_ft_strdup(word[i], "export"));
		save_value = return_value;
		i++;
	}
	if (return_value >= 1)
		return_value = 1;
	return (return_value);
}

char	**change_env(char *str)
{
	char	**new_list;
	int		i;
	int		j;
	int		oldsize;

	i = 0;
	j = 0;
	oldsize = get_envp_size() - 1;
	new_list = malloc_env(oldsize + 3);
	i = 0;
	while (g_envp_list[i] != NULL)
	{
		if (i != 0 && check_dup(str, g_envp_list[i]))
			return (change_env_at_export(str, new_list, i));
		if (i == oldsize)
			new_list[j++] = str;
		new_list[j++] = safe_ft_strdup(g_envp_list[i++], "change_env");
	}
	new_list[j] = NULL;
	free_env(g_envp_list);
	return (new_list);
}

char	**change_env_at_export(char *str, char **new_list, int i)
{
	if (check_dup(str, g_envp_list[i]) == 2)
		free(str);
	else
	{
		free(g_envp_list[i]);
		g_envp_list[i] = str;
	}
	free_env(new_list);
	return (g_envp_list);
}

int	check_export_word(char *word, int *fd)
{
	int	j;

	j = 0;
	if (ft_isalpha(word[0]) == 0 && word[0] != '_')
		return (error_print_export("not a valid identifier", word, fd));
	while (word[j] != '\0' && word[j] != '=')
	{
		if (!(ft_isalnum(word[j]) || word[j] == '_'))
			return (error_print_export("not a valid identifier", \
			word, fd));
		j++;
	}
	return (0);
}
