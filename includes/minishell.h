/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 04:00:58 by jaeyjeon         ###   ########.fr       */
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
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1,
	STD_ERROR = 2
};

/*signal*/
void	set_signal(void);;
void	catch_signal(int signum);
void	do_sigint(pid_t pid);
void	do_sigquit(pid_t pid);
void	do_sigterm(void);
/*get_env*/
char	**get_env(char **envp);
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

/* msh_executor */
int		msh_executor(t_tree *tree, char **envp_list);
pid_t	*msh_executor_fork(t_node *pipe_nd, char **envp_list, pid_t *pids);
int		msh_executor_wait_child(int *pids);
char	**msh_executor_get_path(char **envp_list);
pid_t	*msh_executor_malloc_pids(t_tree *tree);
int		msh_exit_status(int statloc);

/* msh_run_cmd */
int		msh_run_cmd(t_node *cmd_nd, int fd[2], char **envp_list);
int		msh_run_simp_cmd(t_node *cmd_nd, char **envp_list);
char	*msh_get_cmd_path(char *cmd, char **envp_list);

/* msh _redirection */
int		msh_redirection(t_node *redirct_nd, int *fd);
int		*msh_set_redirection(t_node *redirct_nd, int *fd);
int		msh_set_redirection_open(t_node *redirct_nd, int *fd);
int		*msh_create_redirect_fd(void);


int		*msh_nopipe_builtin_redirection(t_node *redirct_nd);

/* msh_error */
void	msh_print_errno(char *str);

/* msh_run_builtin.c */
int		msh_run_builtin(t_node *simp_cmd, int *fd, char **envp_list);
int		msh_nopipe_builtin(t_tree *tree, char **envp_list);
int		msh_is_builtin(t_node *simp_cmd_nd);
int		*msh_init_fd(void) ;


#endif
