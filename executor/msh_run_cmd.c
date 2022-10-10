/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:47 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/10 13:00:33 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_run_cmd(t_node *cmd_nd, int *fd, char **envp_list)
{
	int	rtn;

	rtn = -1;
	if (msh_redirection(cmd_nd->left, fd) == -1)
		return (1);
	rtn = msh_run_builtin(cmd_nd->right, fd, envp_list);
	if (rtn != -1)
		return (rtn);
	msh_run_simp_cmd(cmd_nd->right, envp_list); //envp_path...
	if (errno == 14) //str1 이 존재하지 않는 경우도 있나요
	{
		msh_print_error_str(cmd_nd->right->str1, "command not found", fd);
		return (127);
	}
	else if (errno == 13)
	{
		msh_print_errno(cmd_nd->right->str1, fd);
		return (126);
	}
	else
		msh_print_errno(cmd_nd->right->str1, fd);
	return (1);
}

int	msh_run_simp_cmd(t_node *cmd_nd, char **envp_list)
{
	char	*file_path;
	char	**cmd_argv;

	file_path = msh_get_cmd_path(cmd_nd->str1, envp_list);
	cmd_argv = ft_split(cmd_nd->str2, ' ');
	if (file_path == NULL)
		file_path = ft_substr(cmd_argv[0], 0, ft_strlen(cmd_argv[0]));
	execve(file_path, cmd_argv, envp_list);
	return (-1);
}

char	*msh_get_cmd_path(char *cmd, char **envp_list)
{
	char		*cmd_path;
	char		*tmp;
	int			i;
	struct stat	buf;

	i = 0;
	while (envp_list[i])
	{
		tmp = ft_strjoin(envp_list[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &buf) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
