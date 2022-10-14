/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:29:31 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/14 20:37:41 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_run_builtin(t_node *simp_cmd, int *fd)
{
	int	rtn;

	rtn = 0;
	if (simp_cmd->str1 == NULL)
		return (-1);
	if (fd == NULL)
		return (-1);
	if (ft_strncmp(simp_cmd->str1, "echo", 5) == 0)
		rtn = do_echo(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "cd", 3) == 0)
		rtn = do_cd(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "pwd", 3) == 0)
		rtn = do_pwd(fd);
	else if (ft_strncmp(simp_cmd->str1, "export", 7) == 0)
		rtn = do_export(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "unset", 6) == 0)
		rtn = do_unset(simp_cmd->str2, fd);
	else if (ft_strncmp(simp_cmd->str1, "env", 4) == 0)
		rtn = do_env(fd);
	else if (ft_strncmp(simp_cmd->str1, "exit", 5) == 0)
		rtn = do_exit(simp_cmd->str2, fd);
	else
		return (-1);
	return (rtn);
}

int	msh_nopipe_builtin(t_tree *tree)
{
	int		rtn;
	t_node	*cmd_nd;
	t_node	*sim_cmd_nd;
	int		*fd;

	rtn = 1;
	cmd_nd = tree->top->left;
	sim_cmd_nd = cmd_nd->right;
	if (tree->top->right || sim_cmd_nd == NULL || sim_cmd_nd->str1 == NULL)
		return (-1);
	fd = msh_init_fd();
	if (fd == NULL)
		fprintf(stderr, "msh_nopipe_builtin() fd error\n"); // 여기 수정
	if (msh_is_builtin(sim_cmd_nd) == -1)
		return (-1);
	if (msh_set_redirection(cmd_nd->left, fd))
		rtn = msh_run_builtin(sim_cmd_nd, fd);
	if (fd[STD_IN] > 2)
		close(fd[STD_IN]);
	if (fd[STD_OUT] > 2)
		close(fd[STD_OUT]);
	if (fd[STD_ERROR] > 2)
		close(fd[STD_ERROR]);
	free(fd);
	return (rtn);
}

int	msh_is_builtin(t_node *simp_cmd_nd)
{
	if (simp_cmd_nd == NULL || simp_cmd_nd->str1 == NULL)
		return (-1);
	if (ft_strncmp(simp_cmd_nd->str1, "echo", 5) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "cd", 3) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "pwd", 3) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "export", 7) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "unset", 6) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "env", 4) == 0)
		;
	else if (ft_strncmp(simp_cmd_nd->str1, "exit", 5) == 0)
		ft_putstr_fd("exit", STD_OUT);
	else
		return (-1);
	return (1);
}
