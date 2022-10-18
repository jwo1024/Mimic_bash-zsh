/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:02:23 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 17:56:49 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parser.h"
#include "tokenizer.h"

int	msh_parser(t_tree **tokens)
{
	t_tree	*tree;
	int		rtn;
	t_node	*cur_pipe;

	tree = msh_tree_create_tree();
	msh_parse_add_pipe_cmd(tree, NULL, NULL);
	cur_pipe = tree->top;
	while (1)
	{
		rtn = msh_parse_check_type(tree, *tokens, &cur_pipe);
		if (rtn == -2)
		{
			cur_pipe = cur_pipe->right;
			continue ;
		}
		else if (rtn != 0)
		{
			msh_tree_delete(tree);
			tree = NULL;
		}
		break ;
	}
	msh_tree_delete(*tokens);
	*tokens = tree;
	return (rtn);
}

int	msh_parse_check_type(t_tree *tree, t_tree *tokens, t_node **cur_pipe)
{
	int		rtn;
	t_node	*cur_cmd;
	t_node	*next;
	t_node	*curr;

	cur_cmd = (*cur_pipe)->left;
	curr = tokens->top;
	next = tokens->top->left;
	if (curr->type == T_WORD && del_dequot(&curr->str1))
		rtn = msh_parse_word(tree, tokens, cur_cmd, next);
	else if (curr->type == T_REDIR)
		rtn = msh_parse_redirect(tree, tokens, cur_cmd, next);
	else if (curr->type == T_NULL)
		rtn = 0 ;
	else
	{
		msh_parse_error(curr->str1);
		rtn = 258;
	}
	return (rtn);
}

void	msh_parse_error(char *str)
{
	if (str == NULL)
		msh_print_error(STD_ERROR, \
		"syntax error near unexpected token 'newline'", NULL, 1);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '" \
		, STD_ERROR);
		ft_putstr_fd(str, STD_ERROR);
		ft_putstr_fd("'\n", STD_ERROR);
	}
}
