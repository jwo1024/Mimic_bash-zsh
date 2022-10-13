/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:21:21 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/13 15:52:58 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

int	msh_cnt_typewords(t_node *node);

// str2
t_node	*msh_parse_get_tokens_top(t_tree *tree)
{
	t_node	*rtn;

	if (tree == NULL || tree->top == NULL)
		return (NULL);
	rtn = tree->top;
	tree->top = tree->top->left;
	if (tree->top)
		tree->top->parent = NULL;
	if (rtn->left)
		rtn->left = NULL;
	tree->node_count--;
	return (rtn);
}

int	msh_parse_add_redirect(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*redir_node;
	t_node	*file_node;

	if (tree == NULL || tokens == NULL || cur_cmd_nd == NULL)
		return (-1);
	redir_node = msh_parse_get_tokens_top(tokens);
	file_node = msh_parse_get_tokens_top(tokens);
	redir_node->str2 = ft_calloc(2, sizeof(char *));
	if (redir_node->str2 == NULL)
		return (-1);
	redir_node->str2[0] = file_node->str1;
	redir_node->str2[1] = NULL;
	file_node->str1 = NULL;
	if (cur_cmd_nd->left != NULL)
	{
		cur_cmd_nd = cur_cmd_nd->left;
		while (cur_cmd_nd->right)
			cur_cmd_nd = cur_cmd_nd->right;
		cur_cmd_nd->right = redir_node;
	}
	else
		cur_cmd_nd->left = redir_node;
	redir_node->parent = cur_cmd_nd;
	tree->node_count++;
	msh_tree_clear_node(file_node);
	free(file_node);
	return (1);
}

int	msh_parse_add_pipe_cmd(t_tree *tree, t_tree *tokens, t_node *cur_pipe_nd)
{
	t_node	*new_pipe;

	if (tree == NULL)
		return (-1);
	if (tokens == NULL)
		new_pipe = msh_tree_create_node(T_PIPE, NULL);
	else
		new_pipe = msh_parse_get_tokens_top(tokens);
	new_pipe->left = msh_tree_create_node(T_CMD, NULL);
	new_pipe->left->parent = new_pipe;
	if (cur_pipe_nd == NULL && tree->top == NULL)
		tree->top = new_pipe;
	else
		cur_pipe_nd->right = new_pipe;
	return (1);
}

int	msh_parse_add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;
	t_node	*tmp;
	// char	*str; str을 사용중이 아니라서 컴파일시 에러
	int		cnt;

	if (tree == NULL || tokens == NULL || tree->top == NULL \
		|| cur_cmd_nd == NULL || cur_cmd_nd->right != NULL)
		return (-1);
	token = msh_parse_get_tokens_top(tokens);
	token->type = T_SIMP_CMD;
	// str = ft_strdup(token->str1); str을 사용중이 아니라서 컴파일시 에러
	cur_cmd_nd->right = token;
	token->str2 = ft_calloc(msh_cnt_typewords(tokens->top) + 2, sizeof(char *));
	cnt = 0;
	token->str2[cnt++] = ft_strdup(token->str1);
	while (tokens->top->type == T_WORD)
	{
		tmp = msh_parse_get_tokens_top(tokens);
		token->str2[cnt++] = tmp->str1;
		free(tmp);
	}
	token->str2[cnt] = NULL;
	return (1);
}

int	msh_cnt_typewords(t_node *node)
{
	int	cnt;

	cnt = 0;
	while (node->type == T_WORD)
	{
		node = node->left;
		cnt++;
	}
	return (cnt);
}
