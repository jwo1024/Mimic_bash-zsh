/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:02:23 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/09 21:28:47 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

void	msh_print_parse_error(char *str)
{
	if (str == NULL)
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
}

t_tree	*msh_parser(t_tree *tokens)
{
	t_tree	*tree;
	int		rtn;
	t_node	*cur_pipe;

	tree = msh_tree_create_tree();
	msh_parse_add_pipe_cmd(tree, NULL, NULL);
	cur_pipe = tree->top;

	while (1)
	{
		rtn = msh_parse_check_type(tree, tokens, &cur_pipe);
		if (rtn == -1)
		{
			printf("syntax error, something wrong\n"); // 체크용 임시. 
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

int	msh_parse_check_type(t_tree *tree, t_tree *tokens, t_node **cur_pipe)
{
	int		rtn;
	t_node	*cur_cmd;
	t_node	*next;
	t_node	*curr;

	cur_cmd = (*cur_pipe)->left;
	curr = tokens->top;
	next = tokens->top->left;
	if (curr->type == T_WORD)
			rtn = msh_parse_word(tree, tokens, cur_cmd, next);
	else if (curr->type == T_REDIR)
			rtn = msh_parse_redirect(tree, tokens, cur_cmd, next);
	else if (curr->type == T_NULL)
			rtn = 0 ;
	else
	{
		msh_print_parse_error(curr->str1);
		rtn = -1;
	}
	return (rtn);
}

int	msh_parse_redirect(t_tree *tree, t_tree *tokens, \
							t_node *cur_cmd, t_node *cur_token)
{
	int		rtn;
	t_node	*next;
	t_node	*curr;

	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_token == NULL)
		return (-1);
	if (cur_token->type == T_WORD)
	{
		msh_parse_add_redirect(tree, tokens, cur_cmd);

		curr = tokens->top;
		next = tokens->top->left;
		if (curr->type == T_WORD)
			rtn = msh_parse_word(tree, tokens, cur_cmd, next);
		else if (curr->type == T_REDIR)
			rtn = msh_parse_redirect(tree, tokens, cur_cmd, next);
		else if (curr->type == T_PIPE)
			rtn = msh_parse_pipe(tree, tokens, &cur_cmd->parent);
		else if (curr->type == T_NULL)
			rtn = 0;
		else
		{
			rtn = -1;
			msh_print_parse_error(tokens->top->str1);
		}
	}
	else
	{
		rtn = -1;
		msh_print_parse_error(cur_token->str1);
	}
	return (rtn);

}

int	msh_parse_word(t_tree *tree, t_tree *tokens, \
						t_node *cur_cmd, t_node *cur_tokens)
{
	int		rtn;
	t_node	*next;
	t_node	*curr;

	if (tree == NULL || tokens == NULL || cur_cmd == NULL || cur_tokens == NULL)
		return (-1);
	if (cur_tokens->type == T_WORD)
		rtn = msh_parse_word(tree, tokens, cur_cmd, cur_tokens->left);
	else
	{
		if (msh_parse_add_simcmd(tree, tokens, cur_cmd) == -1)
			return (-1);
		curr = tokens->top;
		next = tokens->top->left;
		if (curr->type == T_WORD)
			rtn = msh_parse_word(tree, tokens, cur_cmd, next);
		else if (curr->type == T_REDIR)
			rtn = msh_parse_redirect(tree, tokens, cur_cmd, next);
		else if (curr->type == T_PIPE)
			rtn = msh_parse_pipe(tree, tokens, &cur_cmd->parent);
		else if (curr->type == T_NULL)
			rtn = 0;
		else
		{
			msh_print_parse_error(curr->str1);
			rtn = -1;
		}
	}
	return (rtn);
}

int	msh_parse_pipe(t_tree *tree, t_tree *tokens, t_node **cur_pipe)
{
	int		rtn;
	t_node	*next;
	t_node	*cur_cmd;

	rtn = msh_parse_add_pipe_cmd(tree, tokens, *cur_pipe);
	*cur_pipe = (*cur_pipe)->right;
	next = tokens->top->left;
	cur_cmd = (*cur_pipe)->left;
	if (tokens->top->type == T_WORD)
		rtn = 1;
	else if (tokens->top->type == T_REDIR)
		rtn = 1;
	else
	{
		msh_print_parse_error(tokens->top->str1);
		rtn = -1;
	}
	return (rtn);
}
