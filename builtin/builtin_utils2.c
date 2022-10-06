/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:57:21 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 21:36:52 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(int fd)
{
	char	**copy_env;
	int		i;

	copy_env = sort_env();
	i = 0;
	while (copy_env[i] != NULL)
	{
		print_env_print_part(copy_env[i], fd);
		i++;
	}
	free_env(copy_env);
}

char	**sort_env(void)
{
	int		i;
	int		j;
	char	**new;
	char	*temp;

	i = 0;
	while (g_envp_list[i] != NULL)
		i++;
	new = malloc_env(i + 1);
	i = -1;
	while (g_envp_list[++i] != NULL)
		new[i] = ft_strdup(g_envp_list[i]);
	i = -1;
	while (new[++i] != NULL)
	{
		j = i;
		while (new[++j])
		{
			if (ft_strncmp(new[i], new[j], ft_strlen(new[i])) > 0)
			{
				temp = new[i];
				new[i] = new[j];
				new[j] = temp;
			}
		}
	}
	return (new);
}

void	print_env_print_part(char *str, int fd)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", fd);
	while (str[i] != '\0')
	{
		write(fd, &str[i], fd);
		if (str[i] == '=')
			ft_putstr_fd("\"", fd);
		i++;
	}
	ft_putstr_fd("\"", fd);
	ft_putstr_fd("\n", fd);
	str[0] = -1;
}
