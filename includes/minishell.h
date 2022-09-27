/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/27 21:30:37 by jaeyjeon         ###   ########.fr       */
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
# include "../libft/libft.h"
# include "msh_tree.h"

/*signal*/
void	set_signal(void);;
void	catch_signal(int signum);
void	do_sigint(pid_t pid);
void	do_sigquit(pid_t pid);
void	do_sigterm(void);
/*get_env*/
t_list	*get_env(char **envp);
/*utils*/
void	ft_putstr_fd(char *s, int fd);

/*parser*/
t_tree	*msh_parser(t_tree *tokens);
int		msh_parse_check_type(t_tree *tree, t_tree *tokens, t_node **cur_pipe);
int		msh_parse_redirect(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd, t_node *cur_tokens_node);
int		msh_parse_word(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd, t_node *cur_tokens_node);
int		msh_parse_pipe(t_tree *tree, t_tree *tokens, t_node **cur_pipe_nd);
/* msh_parser2.c */
t_node	*msh_parse_get_tokens_top(t_tree *tree);
int		msh_parse_add_redirect(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd);
int		msh_parse_add_pipe_cmd(t_tree *tree, t_tree *tokens, t_node *cur_pipe_nd);
int		msh_parse_add_simcmd(t_tree *tree, t_tree *tokens, t_node *cur_cmd_nd);

/*builtin*/
int		do_pwd(int fd);
int		check_word(char *word);
int		do_exit(char *word);
int		do_echo(char *word, int fd);
int		do_env(t_list *env_list, int fd);
int		check_opt(char *s);
int		check_dequot(char *s);
char	*del_dequot(char *s);
void	do_del_dequot(char *new_str, char *s, char c, t_index *idx);

#endif
