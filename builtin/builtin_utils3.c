/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:54:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/16 20:55:30 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

char	*safe_ft_strjoin(char *s1, char *s2, char *s3)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (new == NULL)
		malloc_failed(s3);
	return (new);
}

char	*safe_ft_strdup(char *s1, char *s2)
{
	char	*new;

	new = ft_strdup(s1);
	if (new == NULL)
		malloc_failed(s2);
	return (new);
}

char	*safe_ft_substr(char *s1, int start, int size, char *s2)
{
	char	*new;

	new = ft_substr(s1, start, size);
	if (new == NULL)
		malloc_failed(s2);
	return (new);
}
