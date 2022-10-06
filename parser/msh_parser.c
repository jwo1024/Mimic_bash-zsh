/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:02:23 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/06 19:16:10 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

// pipe 하나만 들어왔을때 체크 못하는 문제
// 모든 노드의 str1이 존재한다는 전제
// 2> str1에 저장되어 있지 않은것 같음? 

void	msh_error_parse(char *str)
{
	if (str == NULL)
		fprintf(stderr, "minishell: syntax error near unexpected token 'newline'\n");
	else
		fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n", str);
}

t_tree	*msh_parser(t_tree *tokens)
{
	t_tree	*tree;
	int		rtn;
	t_node	*cur_pipe_nd;

	tree = msh_tree_create_tree();
	msh_parse_add_pipe_cmd(tree, NULL, NULL);
	cur_pipe_nd = tree->top;
	while (tokens->top)
	{
		rtn = msh_parse_check_type(tree, tokens, &cur_pipe_nd);
		if (rtn == -1)
		{
		//	printf("syntax error, something wrong\n");
			msh_tree_delete(tree);
			msh_tree_delete(tokens);
			return (NULL);
		}
		else if (rtn == 0)
			break ;
	}
	msh_tree_delete(tokens);
	return (tree);
}

int	msh_parse_check_type(t_tree *tree, t_tree *tokens, t_node **cur_pipe)
{
	int	rtn;

	if (tokens->top->type == T_WORD)
		rtn = msh_parse_word(tree, tokens, (*cur_pipe)->left, tokens->top->left);
	else if (tokens->top->type == T_REDIR)
		rtn = msh_parse_redirect(tree, tokens, (*cur_pipe)->left, tokens->top->left);
	else if (tokens->top->type == T_PIPE)
		rtn = msh_parse_pipe(tree, tokens, cur_pipe);
	else if (tokens->top->type == T_NULL)
		rtn = 0;
	else
	{
		fprintf(stderr, "minishell: syntax error: fail check type %s\n", tokens->top->str1);
		rtn = -1;
	}
	return (rtn);
}

int	msh_parse_redirect(t_tree *tree, t_tree *tokens, \
							t_node *cur_cmd, t_node *cur_token)
{
	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_token == NULL)
		return (-1);
	if (cur_token->type == T_WORD)
	{
		msh_parse_add_redirect(tree, tokens, cur_cmd);
		return (1);
	}
	else
	{
		msh_error_parse(cur_token->str1);
		fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n", cur_token->str1);
		return (-1);
	}
}

int	msh_parse_word(t_tree *tree, t_tree *tokens, \
						t_node *cur_cmd, t_node *cur_tokens)
{
	int	rtn;

	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_tokens == NULL)
		return (-1);
	if (cur_tokens->type == T_WORD)
		rtn = msh_parse_word(tree, tokens, cur_cmd, cur_tokens->left);
	else
	{
		if (msh_parse_add_simcmd(tree, tokens, cur_cmd) == -1)
		{
			msh_error_parse(cur_tokens->str1);
		//	fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n", cur_tokens->str1);
			printf("Error : msh_parse_add_simcmd()\n");
			return (-1);
		}
		return (1);
	}
	return (rtn);
}

int	msh_parse_pipe(t_tree *tree, t_tree *tokens, t_node **cur_pipe_nd)
{
	int	rtn;

	rtn = msh_parse_add_pipe_cmd(tree, tokens, *cur_pipe_nd);
	*cur_pipe_nd = (*cur_pipe_nd)->right;
	if (tokens->top->type == T_PIPE) // && || . 
	{
		msh_error_parse(tokens->top->str1);
	//	fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n", tokens->top->str1);
		return (-1);
	}
	return (rtn);
}
