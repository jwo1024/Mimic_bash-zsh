/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:21:21 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 20:58:10 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parser.h"
#include "builtin.h"

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
	int		rtn;

	if (tree == NULL || tokens == NULL || cur_cmd_nd == NULL)
		return (-1);
	redir_node = msh_parse_get_tokens_top(tokens);
	file_node = msh_parse_get_tokens_top(tokens);
	redir_node->str2 = safe_ft_calloc(2, sizeof(char *), "fail add_redirect");
	redir_node->str2[0] = file_node->str1;
	redir_node->str2[1] = NULL;
	if (cur_cmd_nd->left != NULL)
	{
		cur_cmd_nd = cur_cmd_nd->left;
		while (cur_cmd_nd->left)
			cur_cmd_nd = cur_cmd_nd->left;
	}
	cur_cmd_nd->left = redir_node;
	redir_node->parent = cur_cmd_nd;
	tree->node_count++;
	free(file_node);
	rtn = 0;
	if (ft_strncmp(redir_node->str1, "<<", 3) == 0)
		rtn = msh_heredoc(*redir_node->str2, redir_node);
	return (rtn);
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
	if (new_pipe == NULL)
		exit(msh_print_errno(STD_ERROR, "fail add_pipe_cmd", NULL, 1));
	new_pipe->left = msh_tree_create_node(T_CMD, NULL);
	new_pipe->left->parent = new_pipe;
	if (cur_pipe_nd == NULL && tree->top == NULL)
		tree->top = new_pipe;
	else
		cur_pipe_nd->right = new_pipe;
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
