/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:41 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/07 16:02:45 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

int	msh_executor(t_tree *tree, char **envp_list)
{
	pid_t	*pids;
	int		rtn;
	char	**env_path;

	if (tree == NULL)
		return (258); // syntax error
	env_path = msh_executor_get_path(envp_list);
	rtn = -1;
	if (tree->top->right == NULL)
		rtn = msh_nopipe_builtin(tree, envp_list);
	if (rtn == -1) // 1개 cmd이면서 builtin이면 -1이 아닌 수를 뱉는다. 
	{
		pids = msh_executor_malloc_pids(tree);
		if (pids == NULL)
			return (-1);
		if (rtn == -1)
			msh_executor_fork(tree->top, env_path, pids);
		rtn = msh_executor_wait_child(pids);
	}
	// $?시 출력할 rtn 저장.. 

	return (rtn);
}

/* fork wait*/
pid_t	*msh_executor_fork(t_node *pipe_nd, char **env_path, pid_t *pids)
{
	int	i;
	int	pipe_fd[2];
	int	*fd;

	i = 0;
	fd = msh_init_fd();
	while (pipe_nd)
	{
		if (pipe_nd->right)
		{
			pipe(pipe_fd); // if -1 ? 
			fd[STD_OUT] = pipe_fd[PIPE_IN]; 
		}
		else
			fd[STD_OUT] = STD_OUT;
	

		pids[i] = fork();
		if (pids[i++] == 0)
		{
			if (pipe_nd->right)
				close(pipe_fd[PIPE_OUT]);
			exit(msh_run_cmd(pipe_nd->left, fd, env_path));
		}
	

		if (fd[STD_IN] > 2)
				close(fd[STD_IN]);
		if (pipe_nd->right)
		{
			fd[STD_IN] = pipe_fd[PIPE_OUT];
			close(fd[STD_OUT]);
		}
		pipe_nd = pipe_nd->right;
	}
	// 한번 fd 흐름 따라서 다 닫혔는지 확인필요  lsof -p <pid>
	return (pids);
}

int	msh_executor_wait_child(int *pids)
{
	int	i;
	int	statloc;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &statloc, 0); // NULL options. .
		i++;
	}
	// 마지막 statloc 해석
	// rtn (마지막 종료상태 ) ;
	return (msh_exit_status(statloc));
}



/* utils */
char	**msh_executor_get_path(char **envp_list)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	while (envp_list[i])
	{
		if (ft_strncmp(envp_list[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp_list[i], ':');
			tmp = path[0];
			path[0] = ft_substr(path[0], 5, ft_strlen(path[0]) - 5);
			free(tmp);
			return (path);
		}
		i++;
	}
	return (NULL);
}

pid_t	*msh_executor_malloc_pids(t_tree *tree)
{
	t_node *pipe_nd;
	int		cnt;
	pid_t	*pids;

	pipe_nd = tree->top;
	cnt = 0;
	while (pipe_nd)
	{
//		if (pipe_nd->type != T_PIPE)
//			return (NULL);
		pipe_nd = pipe_nd->right;
		cnt++;
	}
	pids = ft_calloc(cnt + 1, sizeof(pid_t));
	return (pids);
}

int	msh_exit_status(int statloc)
{
	if ((statloc & 255) == 0)
		return ((statloc & 65280) >> 8);
	fprintf(stderr, "exit status error %d, %d, %d\n", statloc & 255, statloc >> 8, statloc << 8);
	return ((statloc & 127) + 128); // signal no + 128
}
