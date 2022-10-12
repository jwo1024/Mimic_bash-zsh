/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:02:23 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/12 23:42:04 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

t_tree	*msh_parser(t_tree *tokens)
{
	t_tree	*tree;
	int		rtn;
	t_node	*cur_pipe;

	if (tokens == NULL) // 존재하지않는 환경변수 하나만 입력받았을때 NULL이 들어오면 바로 끝내줘야해서 추가했습니다
		return (NULL);
	tree = msh_tree_create_tree();
	msh_parse_add_pipe_cmd(tree, NULL, NULL);
	cur_pipe = tree->top;
	while (1)
	{
		rtn = msh_parse_check_type(tree, tokens, &cur_pipe);
		if (rtn == -1)
		{
			msh_tree_delete(tree);
			msh_tree_delete(tokens);
			return (NULL);
		}
		else if (rtn == 0)
			break ;
		cur_pipe = cur_pipe->right;
	}
	msh_tree_delete(tokens);
	return (tree);
}


// msh_parse_check_type_pipe
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
		msh_error_parse(curr->str1);
		rtn = -1;
	}
	return (rtn);
}

int	msh_parse_redirect(t_tree *tree, t_tree *tokens, \
							t_node *cur_cmd, t_node *cur_token)
{
	int		rtn;
	t_node	*next;

	rtn = -1;
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_token == NULL)
		return (rtn);
	if (cur_token->type == T_WORD && del_dequot(&cur_token->str1))
	{
		msh_parse_add_redirect(tree, tokens, cur_cmd);
		/* 함수 나누기 msh_parse_check_alltype */
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
			msh_error_parse(tokens->top->str1);
	}
	else
		msh_error_parse(cur_token->str1);
	return (rtn);
}

int	msh_parse_word(t_tree *tree, t_tree *tokens, \
						t_node *cur_cmd, t_node *cur_tokens)
{
	int		rtn;
	t_node	*next;

	rtn = -1;
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_tokens == NULL)
		return (rtn);
	if (cur_tokens->type == T_WORD && del_dequot(&cur_tokens->str1))
		rtn = msh_parse_word(tree, tokens, cur_cmd, cur_tokens->left);
	else
	{
		if (msh_parse_add_simcmd(tree, tokens, cur_cmd) == -1)
			return (rtn);
		/* 함수 나누기 msh_parse_check_alltype */
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
			msh_error_parse(tokens->top->str1);
	}
	return (rtn);
}

int	msh_parse_pipe(t_tree *tree, t_tree *tokens, t_node **cur_pipe)
{
	int		rtn;

	rtn = msh_parse_add_pipe_cmd(tree, tokens, *cur_pipe);
	if (tokens->top->type == T_WORD && del_dequot(&tokens->top->str1))
		rtn = 1;
	else if (tokens->top->type == T_REDIR)
		rtn = 1;
	else
	{
		msh_error_parse(tokens->top->str1);
		rtn = -1;
	}
	return (rtn);
}
