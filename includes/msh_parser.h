/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 18:47:31 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_PARSER_H
# define MSH_PARSER_H

# include "msh_tree.h"
# include "msh_error.h"
# include "minishell.h"

/*parser*/
int		msh_parser(t_tree **tokens);
int		msh_parse_check_type(t_tree *tree, t_tree *tokens, t_node **cur_pipe);
int		msh_parse_redirect(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd, t_node *cur_tokens_node);
int		msh_parse_word(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd, t_node *cur_tokens_node);
int		msh_parse_pipe(t_tree *tree, t_tree *tokens, t_node **cur_pipe_nd);
void	msh_parse_error(char *str);

/* msh_parser2.c */
t_node	*msh_parse_get_tokens_top(t_tree *tree);
int		msh_parse_add_redirect(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd);
int		msh_parse_add_pipe_cmd(t_tree *tree, t_tree *tokens, t_node *cur_pipe_nd);
int		msh_parse_add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd);
int		msh_cnt_typewords(t_node *node);

/* heredoc */
int		msh_heredoc(char *key, t_node *node);

#endif
