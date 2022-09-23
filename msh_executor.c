
#include "minishell.h"
#include "msh_tree.h"

#include <unistd.h>

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1
};

int	msh_executor(t_tree *tree) // env.. 
{
	/*
	int	i;

	if (pipe(info->fd.pipe) == -1)
		return (error("Error : pipex() fail pipe ", 1));
	i = 0;
	while (i < 2)
	{
		info->pid[i] = fork();
		if (info->pid[i] == -1)
			error("Error : pipex() fail fork ", -1);
		else if (info->pid[i] == 0)
			exit(pipex_child_process(info, i));
		i++;
	}
	close(info->fd.pipe[0]);
	close(info->fd.pipe[1]);
	waitpid(info->pid[0], &info->status[0], 0);
	waitpid(info->pid[1], &info->status[1], 0);
	if (info->status[0] == 0 && info->status[1] == 0)
		return (0);
	return (wait_exit_status(info->status[1]));
	*/

	t_node	*pipe_nd;
//	int		*pid;
	int		pipe_fd[2];
	int		fd[2];

	pipe_nd = tree->top;
	fd[STD_IN] = STD_IN;
	fd[STD_OUT] = STD_OUT;
	while (pipe_nd)
	{
		if (pipe_nd->right)
		{
			pipe(pipe_fd);
			fd[STD_OUT] = pipe_fd[PIPE_IN];
			if (fd[STD_IN] > 2)
				close(fd[STD_IN]);
		}
		else
			fd[STD_OUT] = STD_OUT;
	//	fork();
		if (fork() == 0)
		{
			close(pipe_fd[PIPE_OUT]);
			// run_cmd(pipe_nd, fd[], env);

			printf("fd[STD_IN] %d, fd[STD_OUT] %d\n", fd[STD_IN], fd[STD_OUT]);
			sleep(5);
			exit(0);
		}
		pipe_nd = pipe_nd->right;
		fd[STD_IN] = pipe_fd[PIPE_OUT];
		close(pipe_fd[PIPE_IN]);
	}
	sleep(10);
	return (1);
}

