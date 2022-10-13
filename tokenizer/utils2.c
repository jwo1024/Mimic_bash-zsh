/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:38:59 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 22:27:53 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"
#include "tokenizer.h"

t_node	*split_str(char *str)
{
	t_node		*start;
	int			i;
	int			save;

	i = 0;
	start = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == -1)
			i++;
		else
		{
			save = i;
			while (str[i] != -1 && str[i] != '\0')
				i++;
			if (start == NULL)
				start = make_new(&str[save], i - save);
			else
				add_next(make_new(&str[save], i - save), start);
		}
	}
	if (start == NULL)
		start = make_new(NULL, 0);
	else
		add_next(msh_tree_create_node(T_NULL, NULL), start);
	return (start);
}

t_node	*make_new(char *str, int size)
{
	t_node	*new;
	char	*new_str;
	int		type;

	if (size == 0)
		return (NULL);
	new_str = ft_substr(str, 0, size);
	if (new_str[0] == '|')
		type = T_PIPE;
	else if (new_str[0] == '<')
	{
	//	if (new_str[1] == '<')
	//		type = T_HEREDOC;
	//	else
			type = T_REDIR;
	}
	else if (new_str[0] == '>')
		type = T_REDIR;
	else
		type = T_WORD;
	new = msh_tree_create_node(type, new_str);
	return (new);
}

void	add_next(t_node *new, t_node *start)
{
	t_node	*curr;

	curr = start;
	while (curr->left != NULL)
		curr = curr->left;
	curr->left = new;
}

void	do_change_redir(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op && s[idx->i + 1] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else if (s[idx->i] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}

void	do_change_each_oper(char *str, char *s, t_index *idx, char op)
{
	if (s[idx->i] == op)
	{
		str[idx->j++] = -1;
		str[idx->j++] = s[idx->i++];
		str[idx->j++] = -1;
	}
	else
		str[idx->j++] = s[idx->i++];
}
