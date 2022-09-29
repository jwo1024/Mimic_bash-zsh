/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/29 18:14:58 by jiwolee          ###   ########seoul.kr  */
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1
};

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

/* msh_executor */
int	msh_executor(t_tree *tree, char **envp_list);
pid_t	*msh_executor_fork(t_node *pipe_nd, char **env_path, pid_t *pids);
int		msh_executor_wait_child(int *pids);
char	**msh_executor_get_path(char **envp_list);
pid_t	*msh_executor_malloc_pids(t_tree *tree);


/* msh_run_cmd */
int		msh_run_cmd(t_node *cmd_nd, int fd[2], char **envp_list);
int		msh_run_simp_cmd(t_node *cmd_nd, char **env_path);
char	*msh_get_cmd_path(char *cmd, char **env_path);

/* msh _redirection */
int		msh_redirection(t_node *redirct_nd, int fd[2]);
int		msh_set_redirection(t_node *redirct_nd, int	fd[2]);


#endif
