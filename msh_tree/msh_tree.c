/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:38:29 by jiwolee           #+#    #+#             */
/*   Updated: 2022/09/23 15:40:18 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"./msh_tree.h"

t_tree	*msh_tree_create_tree(void)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(sizeof(t_tree));
	if (new_tree == NULL)
		return (NULL);
	new_tree->top = NULL;
	new_tree->node_count = 0;
	return (new_tree);
}

t_node	*msh_tree_create_node(enum e_ttype type, char *str)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	new_node->str1 = str;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return (new_node);
}

int	msh_tree_add_node_left(t_tree *tree, t_node *cur_node, t_node *new_node)
{
	if (cur_node->left != NULL)
		return (-1);
	cur_node->left = new_node;
	new_node->parent = cur_node;
	tree->node_count++;
	return (1);
}

int	msh_tree_add_node_right(t_tree *tree, t_node *cur_node, t_node *new_node)
{
	if (cur_node->right != NULL)
		return (-1);
	cur_node->right = new_node;
	new_node->parent = cur_node;
	tree->node_count++;
	return (1);
}

int	msh_tree_add_edge_right(t_tree *tree, t_node *new_node)
{
	t_node	*cur_node;

	if (tree == NULL || new_node == NULL)
		return (-1);
	else if (tree->top == NULL)
		tree->top = new_node;
	else
	{
		cur_node = tree->top;
		while (cur_node->right)
			cur_node = cur_node->right;
		msh_tree_add_node_right(tree, cur_node, new_node);
	}
	tree->node_count++;
	return (1);
}
