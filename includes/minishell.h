/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 15:49:46 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include "msh_tree.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include "tokenizer.h"
# include "executor.h"
# include "msh_error.h"

//char	**g_envp_list;
/*
enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1,
	STD_ERROR = 2
};*/

/*get_env*/
char	**get_env(char **envp);

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


/* msh_error 
int		msh_print_errno(int fd, char *str1, char *str2, int rtn);
int		msh_print_error(int fd, char *str1, char *str2, int rtn);
*/

/* heredoc */
int		msh_heredoc(char *key, t_node *node);

void	malloc_failed(char *str);
int		check_str_whitespace(char *str);

#endif
