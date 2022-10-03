/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:47 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/03 14:24:08 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include	<errno.h>

/* run */
int	msh_run_cmd(t_node *cmd_nd, int fd[2], char **env_path)
{
	int	rtn;

	rtn = -1;
	if (msh_redirection(cmd_nd->left, fd) == -1)
		fprintf(stderr, "msh_redirection() wrong\n"); // error() 수정
	// msh_set_wordsplit(); //// 더블쿼터 싱글쿼터
	rtn = msh_run_builtin(cmd_nd->right); // msh_run_builin_cmd();
	if (rtn != -1)
		exit(rtn);

	msh_run_simp_cmd(cmd_nd->right, env_path); //envp_path...

	// bash: syntax error near unexpected token `>>' //

	//	./a.txt: No such file or directory
	//	bash: ---: command not found

	fprintf(stderr, "minishell: %s: %s: errno%d\n", cmd_nd->right->str1, strerror(errno), errno);

	return (127); // someting wrong (command not found)
}

int	msh_run_simp_cmd(t_node *cmd_nd, char **env_path)
{
	char	*file_path;
	char	**cmd_argv;

	file_path = msh_get_cmd_path(cmd_nd->str1, env_path);
	cmd_argv = ft_split(cmd_nd->str2, ' ');
	execve(file_path, cmd_argv, env_path);
	// errno 읽어야한다... 
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

int	msh_run_builtin(t_node *cmd_nd)
{
	int	rtn;

	rtn = 0;
	if (cmd_nd->str1 == NULL)
		return (-1);
	/*
		fprintf로 builtin 명령어 임을 임시로 출력하도록 해두었습니다.

		if (ft_strncmp(cmd_nd->str1, "echo", 5) == 0)
			rtn =  msh_builtin_echo();
	*/
	if (ft_strncmp(cmd_nd->str1, "echo", 5) == 0) // fd 어떻게 넘겨줘..? 
		fprintf(stderr, "builtin cmd echo\n");
	else if(ft_strncmp(cmd_nd->str1, "cd", 3) == 0)
		fprintf(stderr, "builtin cmd cd\n");
	else if(ft_strncmp(cmd_nd->str1, "pwd", 3) == 0)
		fprintf(stderr, "builtin cmd pwd\n");
	else if(ft_strncmp(cmd_nd->str1, "export", 7) == 0)\
		fprintf(stderr, "builtin cmd export\n");
	else if(ft_strncmp(cmd_nd->str1, "unset", 6) == 0)
		fprintf(stderr, "builtin cmd unset\n");
	else if(ft_strncmp(cmd_nd->str1, "env", 4) == 0)
		fprintf(stderr, "builtin cmd env\n");
	else if(ft_strncmp(cmd_nd->str1, "exit", 5) == 0)
		fprintf(stderr, "builtin cmd exit\n");	
	else
		return (-1);
	return (rtn);
}
