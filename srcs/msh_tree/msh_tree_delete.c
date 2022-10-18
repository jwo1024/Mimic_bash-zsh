/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:38:36 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 18:38:26 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"msh_tree.h"
#include	"libft.h"
#include	<sys/stat.h>

void	msh_tree_clear_node(t_node *node)
{
	int			i;
	struct stat	buf;

	i = 0;
	if (node == NULL)
		return ;
	if (node->type == T_REDIR && node->str1 \
		&& ft_strncmp(node->str1, "<<", 3) == 0)
	{
		if (node->str2 && node->str2[0] && lstat(node->str2[0], &buf) == 0)
			unlink(node->str2[0]);
	}
	if (node->str1 != NULL)
		free(node->str1);
	if (node->str2 != NULL)
	{
		while (node->str2 && node->str2[i])
			free(node->str2[i++]);
		free(node->str2);
	}
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
