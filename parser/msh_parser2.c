/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:21:21 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/17 15:47:28 by jiwolee          ###   ########seoul.kr  */
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
	int		rtn;

	if (tree == NULL || tokens == NULL || cur_cmd_nd == NULL)
		return (-1);
	redir_node = msh_parse_get_tokens_top(tokens);
	file_node = msh_parse_get_tokens_top(tokens);
	redir_node->str2 = ft_calloc(2, sizeof(char *));
	if (redir_node->str2 == NULL)
		exit(msh_print_errno(STD_ERROR, "fail add_redirect", NULL, 1));
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

int	msh_parse_add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd)
{
	t_node	*token;
	t_node	*tmp;
	int		cnt;
	char	**str2;

	if (tree == NULL || tokens == NULL \
		|| tree->top == NULL || cur_cmd_nd == NULL)
		return (-1);

	/*msh_parse_add_simcmd_new, msh_parse_add_simcmd_append*/
	if (cur_cmd_nd->right == NULL)
	{
		token = msh_parse_get_tokens_top(tokens);
		token->type = T_SIMP_CMD;
		cur_cmd_nd->right = token;
		token->str2 = ft_calloc(msh_cnt_typewords(tokens->top) + 2, sizeof(char *));
		if (token->str2 == NULL)
			exit(msh_print_errno(STD_ERROR, "fail add_simcmd", NULL, 1));
		token->str2[0] = ft_strdup(token->str1);
		if (token->str2[0] == NULL)
			exit(msh_print_errno(STD_ERROR, "fail add_simcmd", NULL, 1));
		token->str2[1] = NULL;
	}
	else
	{
		int	i;

		token = cur_cmd_nd->right;
		i = 0;
		while (token->str2[i])
			i++;
		str2 = ft_calloc(msh_cnt_typewords(tokens->top) + i + 1, sizeof(char *)); // + 
		if (str2 == NULL)
			exit(msh_print_errno(STD_ERROR, "fail add_simcmd", NULL, 1));
		i = 0;
		while (token->str2[i])
		{
			str2[i] = token->str2[i];
			i++;
		}
		str2[i] = NULL;
		free (token->str2);
		token->str2 = str2;
	}

	/* tmp */
	cnt = 1; // while -> 마지막 index에다가 + ..
	// cnt = i;
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
