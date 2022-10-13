/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:52:20 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 17:54:05 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_export(char **word, int *fd)
{
	int		j;
	int		i;

	j = 0;
	while (word[j] != NULL)
		printf("exit : %s\n", word[j++]);

	i = 1;
	j = 0;
	if (word[1] == NULL || word[1][0] == '\0')
		print_env(fd);
	while (word[i] != NULL)
	{
		if (check_export_word(word[i], fd))
			break ;
		g_envp_list = change_env(ft_strdup(word[i]));
		i++;
	}
	return (0);
}

char	*change_str_at_export(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += skip_dquot(&s[i]);
		if (s[i] == ' ')
			s[i] = -1;
		i++;
	}
	return (s);
}

char	**change_env(char *str)
{
	char	**new_list;
	int		i;
	int		j;
	int		oldsize;

	i = 0;
	j = 0;
	while (g_envp_list[i] != NULL)
		i++;
	oldsize = i - 1;
	new_list = malloc_env(i + 3);
	i = 0;
	while (g_envp_list[i] != NULL)
	{
		if (check_dup(str, g_envp_list[i]))
		{
			free(g_envp_list[i]);
			g_envp_list[i] = str;
			free_env(new_list);
			return (g_envp_list);
		}
		if (i == oldsize)
			new_list[j++] = str;
		new_list[j++] = ft_strdup(g_envp_list[i++]);
	}
	new_list[j] = NULL;
	free_env(g_envp_list);
	return (new_list);
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
