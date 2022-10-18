/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:38:45 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 18:38:30 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_TREE_H
# define MSH_TREE_H

enum e_ttype
{
	T_NULL = 0,
	T_WORD = 1,
	T_REDIR = 2,
	T_PIPE = 3,
	T_CMD = 4,
	T_SIMP_CMD = 5,
	T_AND = 6,
	T_OR = 7
};

typedef struct s_node{
	enum e_ttype	type;
	char			*str1;
	char			**str2;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
}	t_node;

typedef struct s_tree
{
	t_node	*top;
	int		node_count;
}	t_tree;

t_tree	*msh_tree_create_tree(void);
t_node	*msh_tree_create_node(enum e_ttype type, char *str);
int		msh_tree_add_node_left(t_tree *tree, t_node *cur_node, \
												t_node *new_node);
int		msh_tree_add_node_right(t_tree *tree, t_node *cur_node, \
												t_node *new_node);

void	msh_tree_clear_node(t_node *node);
void	msh_tree_delete_nodes(t_node *node);
void	msh_tree_delete(t_tree *tree);

#endif
