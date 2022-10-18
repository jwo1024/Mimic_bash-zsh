/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:38:29 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 18:36:11 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"msh_tree.h"
#include	"msh_error.h"

t_tree	*msh_tree_create_tree(void)
{
	t_tree	*new_tree;

	new_tree = (t_tree *)malloc(sizeof(t_tree));
	if (new_tree == NULL)
		exit(msh_print_errno(2, "fail create tree", NULL, 1));
	new_tree->top = NULL;
	new_tree->node_count = 0;
	return (new_tree);
}

t_node	*msh_tree_create_node(enum e_ttype type, char *str)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
		exit(msh_print_errno(2, "fail create tree_node", NULL, 1));
	new_node->type = type;
	new_node->str1 = str;
	new_node->str2 = NULL;
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
