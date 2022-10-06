/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:38:33 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/06 16:06:14 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"./msh_tree.h"
#include	"minishell.h"

int	msh_tree_print_node(t_node *node)
{
	if (node == NULL)
		return (-1);
	printf("node type: %d, str1 %s, str2 %s \n", \
			node->type, node->str1, node->str2);
	return (1);
}

int	msh_tree_print(t_node *node)
{
	if (node)
		msh_tree_print_node(node);
	else
		return (-1);
	msh_tree_print(node->left);
	msh_tree_print(node->right);
	return (1);
}
