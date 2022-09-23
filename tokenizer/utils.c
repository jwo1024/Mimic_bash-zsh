/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:14:34 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/23 00:01:14 by jaeyjeon         ###   ########.fr       */
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
	if (s[i++] == '\"')
	{
		while (s[i] != '\"' && s[i] != '\0')
		{
			if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\''))
				i += 2;
			else
				i++;
		}
	}
	else if (s[i++] == '\'')
	{
		while (s[i] != '\'' && s[i] != '\0')
		{
			if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\''))
				i += 2;
			else
				i++;
		}
	}
	return (i);
}

int	count_dquot(char *s)
{
	int	i;
	int	countsin;
	int	countdou;

	i = 0;
	countsin = 0;
	countdou = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && (s[i + 1] == '\"' || s[i + 1] == '\''))
			i++;
		else if (s[i] == '\"')
			countdou++;
		else if (s[i] == '\'')
			countsin++;
		i++;
	}
	if (countsin % 2 == 0 && countdou % 2 == 0)
		return (0);
	return (1);
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

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !(s))
		return ;
	write(fd, s, ft_strlen(s));
}
