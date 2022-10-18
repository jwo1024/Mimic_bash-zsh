/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:41 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 18:58:42 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_signal.h"
#include "executor.h"
#include "msh_error.h"


static char		**executor_get_path(char **envp_list);
static pid_t	*executor_init_pids(t_tree *tree);
static void		executor_free_env_path(char **env_path);

int	msh_executor(t_tree *tree)
{
	pid_t	*pids;
	int		exit_status;
	char	**env_path;

	if (tree == NULL)
		return (258);
	env_path = executor_get_path(g_envp_list);
	exit_status = -1;
	if (tree->top->right == NULL)
		exit_status = msh_nopipe_builtin(tree);
	if (exit_status == -1)
	{
		pids = executor_init_pids(tree);
		if (pids == NULL)
		{
			executor_free_env_path(env_path);
			return (1);
		}
		msh_executor_fork(tree->top, env_path, pids);
		exit_status = msh_executor_wait_child(pids);
		set_signal();
		free(pids);
	}
	executor_free_env_path(env_path);
	return (exit_status);
}

static char	**executor_get_path(char **envp_list)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (envp_list[i])
	{
		if (ft_strncmp(envp_list[i], "PATH=", 5) == 0)
		{
			tmp = ft_substr(envp_list[i], 5, ft_strlen(envp_list[i]) - 5);
			if (tmp)
			{
				path = ft_split(tmp, ':');
				free (tmp);
			}
			if (path == NULL)
				msh_print_errno(STD_ERROR, "fail get_path", NULL, 1);
			return (path);
		}
		i++;
	}
	return (NULL);
}

static pid_t	*executor_init_pids(t_tree *tree)
{
	t_node	*pipe_nd;
	int		cnt;
	pid_t	*pids;

	pipe_nd = tree->top;
	cnt = 0;
	while (pipe_nd)
	{
		pipe_nd = pipe_nd->right;
		cnt++;
	}
	pids = ft_calloc(cnt + 1, sizeof(pid_t));
	if (pids == NULL)
		msh_print_errno(STD_ERROR, "fail init pids", NULL, 1);
	return (pids);
}

void	executor_free_env_path(char **env_path)
{
	int	i;

	i = 0;
	if (env_path == NULL)
		return ;
	while (env_path[i])
		free(env_path[i++]);
	free(env_path);
}
