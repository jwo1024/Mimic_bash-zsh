/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:41 by jiwolee           #+#    #+#             */
/*   Updated: 2022/09/30 14:53:00 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"

int	msh_executor(t_tree *tree, char **envp_list) // env..
{
	pid_t	*pids;
	int		rtn;
	char	**env_path;

	(void)rtn;
	// 환경변수 PATH 가공하여 이차원배열로 받아오기
	env_path = msh_executor_get_path(envp_list);
	// pipe 존재만큼 pid 배열 생성
	pids = msh_executor_malloc_pids(tree); // process가 1개일 경우에는 ? && built in 일때
	if (pids == NULL)
		return (-1);
	// 자식 프로세스 fork 및 파이프 할당
		// export시 단일 명령어로 실행될때만 적용되는 사안은 자식 프로세스가 아닌 메인 프로세스에서 실행된다고 보아도 무방한가?
	msh_executor_fork(tree->top, env_path, pids);

	rtn = msh_executor_wait_child(pids);
	return (1);
}

/* fork wait*/
pid_t	*msh_executor_fork(t_node *pipe_nd, char **env_path, pid_t *pids)
{
	int		i;
	int		pipe_fd[2];
	int		fd[2];

	i = 0;
	fd[STD_IN] = STD_IN;
	fd[STD_OUT] = STD_OUT;
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
	return (1);
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




