/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:14:28 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/10 22:39:08 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

t_tree	*msh_start_tokenize(char *s)
{
	t_node	*list;
	t_tree	*tokens;

	list = NULL;
	get_env_at_tokenizer(s);
	change_whitespace(s);
	s = change_oper(s);
	s = del_dequot(s);
	printf ("-- %s --\n", s); // 나중에 삭제
	list = split_str(s);
	tokens = msh_tree_create_tree();
	tokens->top = list;
	return (tokens);
}

char	*get_env_at_tokenizer(char *s)
{
	t_index	idx;

	idx.i = 0;
	idx.j = 0;
	while (s[idx.i] != '\0')
	{
		if (s[idx.i] == '$')
		{
			idx.j = idx.i + 1;
			idx.j += is_env(&s[idx.j]);
			printf("환경변수 이름 다음꺼 -> %c(무시하셔도됩니다)\n", s[idx.j]); // 환경변수 이름 끝나고 다음부분
		}
		idx.i++;
	}
	return (s);
}

int	is_env(char *s)
{
	int	i;

	i = 0;
	if (ft_isalpha(s[0]) == 0 && s[0] != '_')
		return (0);
	while (s[i] != '\0' && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (i);
		i++;
	}
	return (i);
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
