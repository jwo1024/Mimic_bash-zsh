/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:02:23 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 15:10:59 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"
#include "libft.h"

int		msh_parser(t_tree **tokens)
{
	t_tree	*tree;
	int		rtn;
	t_node	*cur_pipe;

	if (*tokens == NULL)
		return (0);
	tree = msh_tree_create_tree();
	if (tree == NULL)
		exit(msh_print_errno(STD_ERROR, "fail create tree", NULL, 1));
	msh_parse_add_pipe_cmd(tree, NULL, NULL);
	cur_pipe = tree->top;
	while (1)
	{
		rtn = msh_parse_check_type(tree, *tokens, &cur_pipe);
		if (rtn == -2)
			;
		else if (rtn != 0)
		{
			msh_tree_delete(tree);
			msh_tree_delete(*tokens);
			*tokens = NULL;
			if (rtn == -1)
				rtn = 258;
			return (rtn);
		}
		else if (rtn == 0)
			break ;

		cur_pipe = cur_pipe->right;
	}
	msh_tree_delete(*tokens);
	*tokens = tree;
	return (0);
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
		rtn = -1;
	}
	return (rtn);
}

void	msh_parse_error(char *str)
{
	if (str == NULL)
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", STD_ERROR);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", STD_ERROR);
		ft_putstr_fd(str, STD_ERROR);
		ft_putstr_fd("'\n", STD_ERROR);
	}
}
