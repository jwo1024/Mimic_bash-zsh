/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:14:28 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/23 19:36:33 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

t_tree	*msh_start_tokenize(char *s)
{
	t_node	*list;
	t_node	*curr;
	t_tree	*tokens;

	list = NULL;
	change_whitespace(s);
	s = change_oper(s);
	list = split_str(s);
	curr = list;
	while (curr->left != NULL)
	{
		printf("%s\n", curr->str1);
		curr = curr->left;
	}
	printf("%s\n", curr->str1);
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
			i += skip_dquot(&s[i]);
		if (is_whitespace(s[i]))
			s[i] = -1;
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
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * count_new_space(s, op) + 1);
	if (str == NULL)
		exit(1);
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			k = skip_dquot(&s[i]);
			while (k--)
				str[j++] = s[i++];
		}
		if (s[i] == op)
		{
			str[j++] = -1;
			str[j++] = s[i++];
			str[j++] = -1;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	free(s);
	return (str);
}

char	*change_redir(char *s, char op)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * count_new_space(s, op) + 1);
	if (str == NULL)
		exit(1);
	while (s[i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			k = skip_dquot(&s[i]);
			while (k--)
				str[j++] = s[i++];
		}
		if (s[i] == op && s[i + 1] == op)
		{
			str[j++] = -1;
			str[j++] = s[i++];
			str[j++] = s[i++];
			str[j++] = -1;
		}
		else if (s[i] == op)
		{
			str[j++] = -1;
			str[j++] = s[i++];
			str[j++] = -1;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\0';
	free(s);
	return (str);
}
