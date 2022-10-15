/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:47 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/15 20:16:07 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_run_cmd(t_node *cmd_nd, int *fd, char **env_path)
{
	int	rtn;

	rtn = -1;
	if (msh_redirection(cmd_nd->left, fd) == -1)
		return (1);
	rtn = msh_run_builtin(cmd_nd->right, fd);
	if (rtn != -1)
		return (rtn);
	msh_run_simp_cmd(cmd_nd->right, env_path);
	if (errno == 14)
	{
		msh_print_error(fd[STD_ERROR], cmd_nd->right->str1, "command not found", 127);
		return (127);
	}
	else if (errno == 13)
	{
		msh_print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 127);
		return (127);
	}
	else
		msh_print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 1);
	return (1);
}

int	msh_run_simp_cmd(t_node *simpcmd, char **env_path)
{
	char	*file_path;

	file_path = NULL;
	if ((ft_strrchr(simpcmd->str1, '/') != NULL && file_path == NULL) || env_path == NULL)
		file_path = ft_substr(simpcmd->str2[0], 0, ft_strlen(simpcmd->str2[0]));
	else
		file_path = msh_get_cmd_path(simpcmd->str1, env_path);
	execve(file_path, simpcmd->str2, g_envp_list);
	return (-1);
}

char	*msh_get_cmd_path(char *cmd, char **env_path)
{
	char		*cmd_path;
	char		*tmp;
	int			i;
	struct stat	buf;

	i = 0;
	if (cmd == NULL || cmd[0] == '\0' || env_path == NULL)
		return (NULL);
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &buf) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
