/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:34:28 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 20:17:23 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	get_env_name_size(char *s)
{
	int		i;

	i = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
		return (i + 1);
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
