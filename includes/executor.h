/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 16:01:47 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

//# include "builtin.h"
# include "libft.h"
# include "msh_tree.h"
# include "minishell.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>

/*
char	**g_envp_list;

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1,
	STD_ERROR = 2
};
*/

/* msh_executor */
int		msh_executor(t_tree *tree);
pid_t	*msh_executor_fork(t_node *pipe_nd, char **envp_list, pid_t *pids);
int		msh_executor_wait_child(int *pids);
int		msh_exit_status(int statloc);
/* msh_run_cmd */
int		msh_run_cmd(t_node *cmd_nd, int fd[2], char **envp_list);
int		msh_run_simp_cmd(t_node *simpcmd, char **envp_list);
/* msh _redirection */
int		msh_redirection(t_node *redirct_nd, int *fd);
int		*msh_set_redirection(t_node *redirct_nd, int *fd);
/* msh_run_builtin.c */
int		msh_run_builtin(t_node *simp_cmd, int *fd);
int		msh_nopipe_builtin(t_tree *tree);
int		msh_init_fd(int **fd);

#endif
