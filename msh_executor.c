
#include "minishell.h"
#include "msh_tree.h"

#include <unistd.h>

enum	e_pipe_fd {
	PIPE_OUT = 0,
	PIPE_IN = 1,
	STD_IN = 0,
	STD_OUT = 1
};

char	**msh_executor_get_path(char **envp_list);


int	msh_executor(t_tree *tree, char **envp_list) // env.. 
{
//	pid_t	*pids;
//	int		rtn;
	char	**env_path;

	// 환경변수 PATH 가공하여 이차원배열로 받아오기
	env_path = msh_executor_get_path(envp_list);

	// pipe 존재만큼 pid 배열 생성
	pids = msh_executor_malloc_pids(tree); // process가 1개일 경우에는 ?
	if (pids == NULL)
		return (-1);
	// 자식 프로세스 fork 및 파이프 할당
		// export시 단일 명령어로 실행될때만 적용되는 사안은 자식 프로세스가 아닌 메인 프로세스에서 실행된다고 보아도 무방한가?
	msh_executor_fork(tree->top, env_path, pids);
	// ;

	
	rtn = msh_executor_wait_child(pids);
	// free(tree);
	return (1);
}

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

pid_t	*msh_executor_malloc_pids(tree)
{
	t_node *pipe_nd;
	int		cnt;
	pid_t	*pids;

	pipe_nd = tree->top
	cnt = 0;
	while (pipe_nd)
	{
//		if (pipe_nd->type != T_PIPE)
//			return (NULL);
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
			// exit(msh_run_cmd(pipe_nd->left, fd[], env)); // command_not_found error
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
	// msh_set_wordsplit(); //// 더블쿼터 싱글쿼터
	// msh_run_builtin(); // built in 함수 있는지 검사 (있다면 해당함수명령 실행 exit) (없다면 return)
	// msh_run_simp_cmd(); // exeve(); envp_path
}




/*
int	msh_set_redirection(int fd[2])
{
	// fd redirecition 먼저 하기.
	dup2(fd[STD_IN], STD_IN);
	dup2(fd[STD_OUT], STD_OUT);
	
	while ()
	{

	}

	// 전위 순회하며 redirection 설정하는것 만들기.
	// 맨 위 redirection 실행 -> 다음 실행 -> 다음
	// if heredoc 이면 ? 
}
*/
