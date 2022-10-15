/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:14:34 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/15 19:41:24 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	skip_dquot(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"' && s[i] != '\0')
				i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
				i++;
	}
	if (s[i] == '\"' || s[i] == '\'')
		i++;
	else if (s[i] == '\0')
		return (1);
	return (i);
}

int	count_new_space(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
			i += skip_dquot(&s[i]);
		if (s[i] == c)
			count += 2;
		i++;
	}
	return (i + count);
}
