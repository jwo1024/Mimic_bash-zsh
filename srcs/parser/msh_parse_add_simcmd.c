/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_add_simcmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:12:01 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 17:14:18 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parser.h"

static	void	parse_add_simcmd_new(t_tree *tokens, t_node *cur_cmd_nd);
static	void	parse_add_simcmd_append(t_tree *tokens, t_node *token);

int	msh_parse_add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;
	t_node	*tmp;
	int		cnt;

	if (tree == NULL || tokens == NULL \
		|| tree->top == NULL || cur_cmd_nd == NULL)
		return (-1);
	if (cur_cmd_nd->right == NULL)
		parse_add_simcmd_new(tokens, cur_cmd_nd);
	else
		parse_add_simcmd_append(tokens, cur_cmd_nd->right);
	token = cur_cmd_nd->right;
	cnt = 1;
	while (token->str2[cnt])
		cnt++;
	while (tokens->top->type == T_WORD)
	{
		tmp = msh_parse_get_tokens_top(tokens);
		token->str2[cnt++] = tmp->str1;
		free(tmp);
	}
	token->str2[cnt] = NULL;
	return (1);
}

static void	parse_add_simcmd_new(t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;

	token = msh_parse_get_tokens_top(tokens);
	token->type = T_SIMP_CMD;
	cur_cmd_nd->right = token;
	token->str2 = ft_calloc \
				(msh_cnt_typewords(tokens->top) + 2, sizeof(char *));
	token->str2[0] = ft_strdup(token->str1); //"fail add_simcmd" calloc
	token->str2[1] = NULL;
}

static void	parse_add_simcmd_append(t_tree *tokens, t_node *token)
{
	int		i;
	char	**str2;

	i = 0;
	while (token->str2[i])
		i++;
	str2 = ft_calloc(msh_cnt_typewords(tokens->top) + i + 1, sizeof(char *));
	i = 0; // calloc
	while (token->str2[i])
	{
		str2[i] = token->str2[i];
		i++;
	}
	str2[i] = NULL;
	free (token->str2);
	token->str2 = str2;
}
