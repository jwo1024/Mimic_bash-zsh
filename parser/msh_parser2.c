/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:21:21 by jiwolee           #+#    #+#             */
/*   Updated: 2022/09/25 20:21:18 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

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
	redir_node->str2 = file_node->str1;
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
//	msh_tree_clear_node(file_node);
	// freed was not allocated.. 
	// tokenizer에서 malloc 이 아닌 방법으로 할당되어 저장되는 str이 있는지 확인하기. 
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
	if (cur_pipe_nd == NULL && tree->top == NULL)
		tree->top = new_pipe;
	else
		cur_pipe_nd->right = new_pipe;
	return (1);
}

int	msh_parse_add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;
	char	*str;
	char	*tmp;

	if (tree == NULL || tokens == NULL || \
		cur_cmd_nd == NULL || cur_cmd_nd->right != NULL)
		return (-1);
	token = msh_parse_get_tokens_top(tokens); // token이 잘못되었다면 ?
	token->type = T_SIMP_CMD;
	str = ft_strdup(token->str1);
	cur_cmd_nd->right = token;
	while (tokens->top->type == T_WORD)
	{
		token = msh_parse_get_tokens_top(tokens);
		tmp = ft_strjoin(str, " ");
		free(str);
		str = tmp;
		tmp = ft_strjoin(str, token->str1);
		free(str);
		str = tmp;
		msh_tree_clear_node(token);
		free(token);
	}
	cur_cmd_nd->right->str2 = str;
	return (1);
}
