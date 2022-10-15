/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:14:28 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/15 16:58:19 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

t_tree	*msh_start_tokenize(char *s, int exit_status)
{
	t_node	*list;
	t_tree	*tokens;

	list = NULL;
	s = get_env_at_tokenizer(s, exit_status);
	if (s == NULL)
		return (NULL);
	change_whitespace(s);
	s = change_oper(s);
	list = split_str(s);
	free (s);
	if (list == NULL)
		return (NULL);
	tokens = msh_tree_create_tree();
	tokens->top = list;
	return (tokens);
}

void	change_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			i += skip_dquot(&s[i]);
		}
		else if (is_whitespace(s[i]))
			s[i] = -1;
		else if (s[i] != '\0')
			i++;
	}
}

char	*change_oper(char *s)
{
	s = change_each_oper(s, '|');
	s = change_each_oper(s, ';');
	s = change_redir(s, '<');
	s = change_redir(s, '>');
	return (s);
}

char	*change_each_oper(char *s, char op)
{
	char	*str;
	t_index	*idx;
	int		k;

	idx = make_idx();
	str = malloc(sizeof(char) * count_new_space(s, op) + 1);
	if (str == NULL)
		exit(1);
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"' || s[idx->i] == '\'')
		{
			k = skip_dquot(&s[idx->i]);
			while (k--)
				str[idx->j++] = s[idx->i++];
		}
		do_change_each_oper(str, s, idx, op);
	}
	str[idx->j] = '\0';
	free(s);
	free(idx);
	return (str);
}

char	*change_redir(char *s, char op)
{
	char	*str;
	t_index	*idx;
	int		k;

	idx = make_idx();
	str = malloc(sizeof(char) * count_new_space(s, op) + 1);
	if (str == NULL)
		exit(1);
	while (s[idx->i] != '\0')
	{
		if (s[idx->i] == '\"' || s[idx->i] == '\'')
		{
			k = skip_dquot(&s[idx->i]);
			while (k--)
				str[idx->j++] = s[idx->i++];
		}
		do_change_redir(str, s, idx, op);
	}
	str[idx->j] = '\0';
	free(s);
	free(idx);
	return (str);
}
