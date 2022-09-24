/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:31:54 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/24 17:59:21 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env(char **envp)
{
	t_list	*list_head;
	t_list	*new;
	int		i;

	i = 0;
	while (envp[i])
		i++;
//	list = malloc(sizeof(char *) * (i + 1));
//	if (list == NULL)
///		return (NULL);
	i = 0;
	while (envp[i])
	{
		new = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&list_head, new);
		i++;
	}
	return (list_head);
}
