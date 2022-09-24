
#include "minishell.h"
#include "msh_tree.h"

#include <unistd.h>

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1
};

int	msh_executor(t_tree *tree, char **envp_list) // env.. 
{
	pid_t	*pids;
	int		rtn;
	char	**env_path;

	pids = msh_executor_malloc_pids(tree);
	if (pids == NULL)
		return (-1);
	env_path = msh_executor_get_path(envp_list);
	msh_executor_fork(tree->top, env_path, pids);
	rtn = msh_executor_wait_child(pids);
	// free(tree);
	return (1);
}

pid_t	*msh_executor_malloc_pids(tree)
{
	t_node *pipe_nd;
	int		cnt;
	pid_t	*pids;

	pipe_nd = tree->top
	cnt = 0;
	while (pipe_nd)
	{
		if (pipe_nd->type != T_PIPE)
			return (NULL);
		pipe_nd = pipe_nd->right;
		cnt++;
	}
//	pids = (pid_t *)malloc(sizeof(pid_t) * cnt + 1);
	pids = ft_calloc(cnt + 1, sizeof(pid_t));
	return (pids);
}

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
			pipe(pipe_fd);
			fd[STD_OUT] = pipe_fd[PIPE_IN];
			if (fd[STD_IN] > 2)
				close(fd[STD_IN]);
		}
		else
			fd[STD_OUT] = STD_OUT;
		pids[i] = fork();
		if (pids[i++] == 0)
		{
			close(pipe_fd[PIPE_OUT]);
			// exit(run_cmd(pipe_nd->left, fd[], env));
			printf("fd[STD_IN] %d, fd[STD_OUT] %d\n", fd[STD_IN], fd[STD_OUT]);
			exit(0);
		}
		pipe_nd = pipe_nd->right;
		fd[STD_IN] = pipe_fd[PIPE_OUT];
		close(pipe_fd[PIPE_IN]);
	}
	return (pids);
}


int	msh_run_cmd(t_node *cmd_nd, int fd[2], char **envp_list)
{
	// msh_set_redirection (cmd_nd->left);
	// msh_set_wordsplit(); //// 
	// msh_run_builtin();
	// msh_run_simp_cmd();
}