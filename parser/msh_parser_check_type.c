/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser_check_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:16:19 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 17:35:00 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parser.h"
#include "tokenizer.h"

int	msh_parse_check_alltype(t_tree *tree, t_tree *tokens, t_node *cur_cmd)
{
	int		rtn;
	t_node	*next;

	rtn = 258;
	next = tokens->top->left;
	if (tokens->top->type == T_WORD && del_dequot(&tokens->top->str1))
		rtn = msh_parse_word(tree, tokens, cur_cmd, next);
	else if (tokens->top->type == T_REDIR)
		rtn = msh_parse_redirect(tree, tokens, cur_cmd, next);
	else if (tokens->top->type == T_PIPE)
		rtn = msh_parse_pipe(tree, tokens, &cur_cmd->parent);
	else if (tokens->top->type == T_NULL)
		rtn = 0;
	else
		msh_parse_error(tokens->top->str1);
	return (rtn);
}

int	msh_parse_redirect(t_tree *tree, t_tree *tokens,
							t_node *cur_cmd, t_node *cur_token)
{
	int		rtn;

	rtn = 258;
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_token == NULL)
		return (rtn);
	if (cur_token->type == T_WORD && del_dequot(&cur_token->str1))
	{
		rtn = msh_parse_add_redirect(tree, tokens, cur_cmd);
		if (rtn == 0)
			rtn = msh_parse_check_alltype(tree, tokens, cur_cmd);
	}
	else
		msh_parse_error(cur_token->str1);
	return (rtn);
}

int	msh_parse_word(t_tree *tree, t_tree *tokens, \
						t_node *cur_cmd, t_node *cur_tokens)
{
	int		rtn;

	rtn = 258;
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_tokens == NULL)
		return (rtn);
	if (cur_tokens->type == T_WORD && del_dequot(&cur_tokens->str1))
		rtn = msh_parse_word(tree, tokens, cur_cmd, cur_tokens->left);
	else
	{
		if (msh_parse_add_simcmd(tree, tokens, cur_cmd) == -1)
			return (rtn);
		rtn = msh_parse_check_alltype(tree, tokens, cur_cmd);
	}
	return (rtn);
}

int	msh_parse_pipe(t_tree *tree, t_tree *tokens, t_node **cur_pipe)
{
	int		rtn;

	rtn = msh_parse_add_pipe_cmd(tree, tokens, *cur_pipe);
	if (tokens->top->type == T_WORD && del_dequot(&tokens->top->str1))
		rtn = -2;
	else if (tokens->top->type == T_REDIR)
		rtn = -2;
	else
	{
		msh_parse_error(tokens->top->str1);
		rtn = 258;
	}
	return (rtn);
}
