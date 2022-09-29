/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:47 by jiwolee           #+#    #+#             */
/*   Updated: 2022/09/29 18:14:41 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* run */
int	msh_run_cmd(t_node *cmd_nd, int fd[2], char **env_path)
{
	if (msh_redirection(cmd_nd->left, fd) == -1)
		fprintf(stderr, "msh_redirection() wrong\n");
	// msh_set_wordsplit(); //// 더블쿼터 싱글쿼터
	// msh_run_builtin(); // built in 함수 있는지 검사 (있다면 해당함수명령 실행 exit) (없다면 return)
	// 만약 built in 함수라면 -> 여기서 종료하기.. 

	// $? 이거 어디다 저장해두나요..? ? ? ? ?  ?

	msh_run_simp_cmd(cmd_nd->right, env_path);
	// msh_run_simp_cmd(); // exeve(); envp_path
	return (1);
}

int	msh_run_simp_cmd(t_node *cmd_nd, char **env_path)
{
	char	*file_path;
	char	**cmd_argv;

	file_path = msh_get_cmd_path(cmd_nd->str1, env_path);
	cmd_argv = ft_split(cmd_nd->str2, ' ');
	execve(file_path, cmd_argv, env_path);
	return (-1);
}

char	*msh_get_cmd_path(char *cmd, char **env_path)
{
	char		*cmd_path;
	char		*tmp;
	int			i;
	struct stat	buf;

	i = 0;
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
