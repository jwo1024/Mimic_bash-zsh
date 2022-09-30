/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:21:27 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/27 21:02:45 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_echo(char *word, int fd)
{
	char	*copy_str;
	int		opt;

	opt = 0;
	copy_str = ft_strdup(&word[5]);
	while (check_opt(&copy_str[opt]) != 0)
		opt += check_opt(&copy_str[opt]);
	copy_str = del_dequot(copy_str);
	ft_putstr_fd(&copy_str[opt], fd);
	if (opt == 0 && copy_str[opt] != '\0')
		ft_putstr_fd("\n", fd);
	free (copy_str);
	return (0);
}

int	check_opt(char *s)
{
	int	count;

	count = 0;
	if (ft_strncmp("-n", s, 2) != 0)
		return (0);
	else
	{
		count = 2;
		while (s[count] != '\0')
		{
			if (s[count] == 'n')
				count++;
			else if (s[count] == ' ')
			{
				count++;
				break ;
			}
			else
				return (0);
		}
	}
	return (count);
}

int	check_dequot(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0')
				if (s[i++] == '\"')
					return (1);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0')
				if (s[i++] == '\'')
					return (1);
		}
		else
			i++;
	}
	return (0);
}

char	*del_dequot(char *s)
{
	char	*new_str;
	t_index	*idx;

	idx = make_idx();
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"')
			do_del_dequot(new_str, s, '\"', idx);
		else if (s[idx->i] == '\'')
			do_del_dequot(new_str, s, '\'', idx);
		else
			new_str[idx->j++] = s[idx->i++];
	}
	new_str[idx->j] = '\0';
	free (s);
	free (idx);
	return (new_str);
}

void	do_del_dequot(char *new_str, char *s, char c, t_index *idx)
{
	if (check_dequot(&s[idx->i]))
	{
		idx->i++;
		while (s[idx->i] != c)
			new_str[idx->j++] = s[idx->i++];
		idx->i++;
	}
	else
		new_str[idx->j++] = s[idx->i++];
}
