/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:09:47 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/05 23:10:46 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include	<errno.h>

/* run */
int	msh_run_cmd(t_node *cmd_nd, int *fd, char **envp_list)
{
	int	rtn;

	rtn = -1;
	if (msh_redirection(cmd_nd->left, fd) == -1)
		fprintf(stderr, "msh_redirection() wrong\n"); // error() 수정
	// msh_set_wordsplit(); //// 더블쿼터 싱글쿼터
	rtn = msh_run_builtin(cmd_nd->right, fd, envp_list); // msh_run_builin_cmd();
	if (rtn != -1)
		exit(rtn);

	msh_run_simp_cmd(cmd_nd->right, envp_list); //envp_path...

	// bash: syntax error near unexpected token `>>' //

	//	./a.txt: No such file or directory
	//	bash: ---: command not found

	fprintf(stderr, "minishell: %s: %s: errno%d\n", cmd_nd->right->str1, strerror(errno), errno);

	return (127); // someting wrong (command not found)
}

int	msh_run_simp_cmd(t_node *cmd_nd, char **envp_list)
{
	char	*file_path;
	char	**cmd_argv;

	file_path = msh_get_cmd_path(cmd_nd->str1, envp_list);
	cmd_argv = ft_split(cmd_nd->str2, ' ');
	execve(file_path, cmd_argv, envp_list);
	// errno 읽어야한다... 
	return (-1);
}

char	*msh_get_cmd_path(char *cmd, char **envp_list)
{
	char		*cmd_path;
	char		*tmp;
	int			i;
	struct stat	buf;

	i = 0;
	while (envp_list[i])
	{
		tmp = ft_strjoin(envp_list[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &buf) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}

	return (NULL);
}
