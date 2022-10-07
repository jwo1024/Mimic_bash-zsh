/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:52:20 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/07 14:38:52 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_export(char *word, int fd)
{
	char	*copy_word;
	char	*part;
	t_index	*idx;

	idx = make_idx();
	copy_word = ft_strdup(&word[7]);
	if (word[6] == '\0')
		print_env(fd);
	while (copy_word[idx->j] != '\0')
	{
		while (copy_word[idx->i] != '\0' && copy_word[idx->i] != ' ')
			idx->i++;
		part = ft_substr(copy_word, idx->j, idx->i - idx->j);
		if (check_export_word(part, fd))
			break ;
		g_envp_list = change_env(part);
		if (copy_word[idx->i] == ' ')
			idx->i++;
		idx->j = idx->i;
	}
	free (copy_word);
	return (0);
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
	if (new_list == NULL)
		return (g_envp_list);
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

int	check_export_word(char *word, int fd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word[i] != '=' && word[i] != '\0')
		i++;
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

int	check_dup(char *str, char *env)
{
	int	j;

	j = 0;
	if (str[j] == env[j])
	{
		while (str[j] != '=' && str[j] != '\0')
		{
			j++;
			if (str[j] != env[j])
				break ;
		}
		if ((str[j] == '=' && env[j] == '=') || \
		(str[j] == '\0' && env[j] == '\0'))
			return (1);
	}
	return (0);
}

int	error_print_export(char *str, char *word, int fd)
{
	ft_putstr_fd("minishell: export: ", fd);
	write(fd, "`", 1);
	ft_putstr_fd(word, fd);
	write(fd, "\': ", 2);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	free(word);
	return (1);
}
