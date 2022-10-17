/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor_fork_wait.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:43:26 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 02:01:47 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_signal.h"

pid_t	*msh_executor_fork(t_node *pipe_nd, char **env_path, pid_t *pids)
{
	int	i;
	int	pipe_fd[2];
	int	*fd;

	i = 0;
	if (msh_init_fd(&fd) == -1)
		return (NULL);
	while (pipe_nd)
	{
		msh_executor_fork_set_pipe1(pipe_nd, pipe_fd, fd);
		set_signal_fork(); // signal 수신시 부모는 잠시 출력을 하지않도록 잠금
		pids[i] = fork();
		if (pids[i] == -1)
			msh_print_errno(STD_ERROR, "fail executor_fork", NULL, 1);
		if (pids[i++] == 0)
		{
			if (pipe_nd->right)
				close(pipe_fd[PIPE_OUT]);
			exit(msh_run_cmd(pipe_nd->left, fd, env_path));
		}
		msh_executor_fork_set_pipe2(pipe_nd, pipe_fd, fd);
		pipe_nd = pipe_nd->right;
	}
	free (fd);
	return (pids);
}

void	msh_executor_fork_set_pipe1(t_node *pipe_nd, int *pipe_fd, int *fd)
{
	if (pipe_nd->right)
	{
		if (pipe(pipe_fd) == -1)
		{
			msh_print_errno(STD_ERROR, "executor", NULL, -1);
			pipe_fd[STD_IN] = -1;
			pipe_fd[STD_OUT] = -1;
		}
		fd[STD_OUT] = pipe_fd[PIPE_IN];
	}
	else
		fd[STD_OUT] = STD_OUT;
}

void	msh_executor_fork_set_pipe2(t_node *pipe_nd, int *pipe_fd, int *fd)
{
	if (fd[STD_IN] > 2)
		close(fd[STD_IN]);
	if (pipe_nd->right)
	{
		fd[STD_IN] = pipe_fd[PIPE_OUT];
		close(fd[STD_OUT]);
	}
}

int	msh_executor_wait_child(int *pids)
{
	int	i;
	int	statloc;
	int	exit_status;

	i = 0;
	exit_status = 1;
	if (pids[i] == 0)
		return (exit_status);
	while (pids[i])
	{
		if (pids[i] == -1)
			exit_status = -1;
		waitpid(pids[i], &statloc, 0);
		i++;
	}
	if (exit_status == -1)
		return (1);
	check_fork_signal(statloc);
	exit_status = msh_exit_status(statloc);
	return (exit_status);
}

int	msh_exit_status(int statloc)
{
	// (exitstatus)    (signal no)
	// 00000000      0 0000000
	//               ㄴ 1bit coreflag -> 뭐하는 애인지 모르겟음

	if ((statloc & 255) == 0) // 하위 8비트가 0이면 자식프로세스가 exit()호출을 한 정상종료
		return ((statloc >> 8) & 255); // exit 계산

	return ((statloc & 127) + 128); // signal no 계산 + 128 (시그널 종료시 128을 더해 에러종료를 한다)
}
