
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:29:31 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/05 22:59:51 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	msh_run_builtin(t_node *simp_cmd, int *fd, char **envp_list)
{
	int	rtn;

	rtn = 0;
	(void)envp_list;
	if (simp_cmd->str1 == NULL)
		return (-1);
	if (fd == NULL) // 나중에 지우기
		return (-1);

	if (ft_strncmp(simp_cmd->str1, "echo", 5) == 0)
	{
		fprintf(stderr, "builtin cmd echo \n");
		rtn = do_echo(simp_cmd->str2, fd);
	}
	else if(ft_strncmp(simp_cmd->str1, "cd", 3) == 0)
	{
		fprintf(stderr, "\nbuiltin cmd cd\n");
		rtn = do_cd(simp_cmd->str2, fd);
	}
	else if(ft_strncmp(simp_cmd->str1, "pwd", 3) == 0)
	{
		fprintf(stderr, "\nbuiltin cmd pwd\n");
		rtn = do_pwd(fd);
	}
	else if(ft_strncmp(simp_cmd->str1, "export", 7) == 0)
	{
		fprintf(stderr, "builtin cmd export\n");
		rtn = do_export(simp_cmd->str2, fd);
	}
	else if(ft_strncmp(simp_cmd->str1, "unset", 6) == 0)
	{
		fprintf(stderr, "builtin cmd unset\n");
		rtn = do_unset(simp_cmd->str2);
	}
	else if(ft_strncmp(simp_cmd->str1, "env", 4) == 0)
	{
		fprintf(stderr, "\nbuiltin cmd env\n");
		rtn = do_env(fd);
	}
	else if(ft_strncmp(simp_cmd->str1, "exit", 5) == 0)
	{
		fprintf(stderr, "\nbuiltin cmd exit\n");
		do_exit(simp_cmd->str2, fd);
		// 뒤에 숫자가 들어오면 뒤에 숫자로 exit, 아니면 기존 $? 로 exit
	}
	else
		return (-1);
	return (rtn);
}

int	msh_nopipe_builtin(t_tree *tree, char **envp_list) // + envp_list;
{
	int		rtn;
	t_node	*cmd_nd;
	t_node	*sim_cmd_nd;
	int		*fd;

	rtn = 1;
	cmd_nd = tree->top->left;
	sim_cmd_nd = cmd_nd->right;
	fd = msh_init_fd();
	if (fd == NULL)
		fprintf(stderr, "msh_nopipe_builtin() fd error\n");
	if (tree->top->right || sim_cmd_nd == NULL || sim_cmd_nd->str1 == NULL) // 오른쪽이 있거나, NULL이면 처리
		return (-1);
	if (msh_is_builtin(sim_cmd_nd) == -1)
		return (-1);

	if (msh_set_redirection(cmd_nd->left, fd))
		rtn = msh_run_builtin(sim_cmd_nd, fd, envp_list);
//	if (rtn != 0) // envp_list
//		fprintf(stderr, "cant be happen msh_nopipe_builtin()\n");

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
	else if(ft_strncmp(simp_cmd_nd->str1, "cd", 3) == 0)
		;
	else if(ft_strncmp(simp_cmd_nd->str1, "pwd", 3) == 0)
		;
	else if(ft_strncmp(simp_cmd_nd->str1, "export", 7) == 0)
		;
	else if(ft_strncmp(simp_cmd_nd->str1, "unset", 6) == 0)
		;
	else if(ft_strncmp(simp_cmd_nd->str1, "env", 4) == 0)
		;
	else if(ft_strncmp(simp_cmd_nd->str1, "exit", 5) == 0)
		write(2, "exit\n", 5); //
	else
		return (-1);
	return (1);
}

