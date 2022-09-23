/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:38:36 by jiwolee           #+#    #+#             */
/*   Updated: 2022/09/23 15:42:44 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"./msh_tree.h"

void	msh_tree_delete_node(t_node **node)
{
	if (node == NULL || *node == NULL)
		return ;
	msh_tree_clear_node(*node);
	free(*node);
}

void	msh_tree_clear_node(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->str1 != NULL)
		free(node->str1);
	if (node->str2 != NULL)
		free(node->str2);
}

void	msh_tree_delete_nodes(t_node *node)
{
	if (node == NULL)
		return ;
	msh_tree_delete_nodes(node->left);
	msh_tree_delete_nodes(node->right);
	msh_tree_clear_node(node);
	free (node);
}

void	msh_tree_delete(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->top)
		msh_tree_delete_nodes(tree->top);
	free(tree);
}
