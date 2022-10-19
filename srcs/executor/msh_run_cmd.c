/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:47 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/20 02:03:12 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "msh_error.h"
#include "mini_signal.h"
#include "builtin.h"

static char	*get_cmd_path(char *cmd, char **env_path);

int	msh_run_cmd(t_node *cmd_nd, int *fd, char **env_path)
{
	int	rtn;

	rtn = -1;
	set_terminal_print_on();
	set_signal_origin();
	if (msh_redirection(cmd_nd->left, fd) == -1)
		return (1);
	if (cmd_nd->right == NULL)
		return (0);
	rtn = msh_run_builtin(cmd_nd->right, fd);
	if (rtn != -1)
		return (rtn);
	msh_run_simp_cmd(cmd_nd->right, env_path);
	if (errno == 14)
		return (msh_print_error(fd[STD_ERROR], cmd_nd->right->str1, \
												"command not found", 127));
	else if (errno == 13 || errno == 20)
		return (msh_print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 126));
	else if (errno == 2)
		return (msh_print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 127));
	msh_print_errno(fd[STD_ERROR], cmd_nd->right->str1, NULL, 1);
	return (1);
}

void	msh_run_simp_cmd(t_node *simpcmd, char **env_path)
{
	char	*file_path;

	file_path = NULL;
	if (ft_strrchr(simpcmd->str1, '/') != NULL || env_path == NULL)
	{
		file_path = safe_ft_substr(simpcmd->str2[0], 0, \
					ft_strlen(simpcmd->str2[0]), "simp_cmd");
		if (file_path == NULL)
			return ;
	}
	else
		file_path = get_cmd_path(simpcmd->str1, env_path);
	execve(file_path, simpcmd->str2, g_envp_list);
}

static char	*get_cmd_path(char *cmd, char **env_path)
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
		tmp = safe_ft_strjoin(env_path[i], "/", "get_cmd_path");
		cmd_path = safe_ft_strjoin(tmp, cmd, "get_cmd_path");
		free(tmp);
		if (stat(cmd_path, &buf) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}
