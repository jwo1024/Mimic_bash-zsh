/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:51:50 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/13 22:43:08 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	msh_heredoc(char *key, t_node *node)
{
	char	*file_path;
	pid_t	pid; // waitfork ...
	int		stat_loc;
	int		rtn;

	file_path =  ft_strjoin("/tmp/minishell_heredoc_tmp_", key); // 이미 있는 이름일 경우에는 ?
	pid = fork();
	if (pid == 0)
		exit(msh_heredoc_child(key, file_path));
	waitpid(pid, &stat_loc, 0);
	rtn = msh_exit_status(stat_loc);
	if (rtn != 0) // 오류
		return (rtn);
	free(node->str2[0]);
	node->str2[0] = file_path;
	return (rtn);
}

int	msh_heredoc_child(char *key, char *file_path)
{
	char	*str;
	char	*new;
	char	*tmp;
	int		fd;

	str = ft_calloc(1, sizeof(char));
	str[0] = '\0';
	while (1)
	{
		new = readline("> ");
		if (ft_strncmp(key, new, ft_strlen(key) + 1) != 0)
		{
			tmp = ft_strjoin(str, new);
			free(str);
			free(new);
			str = ft_strjoin(tmp, "\n");
			continue ;
		}
		do_sigterm(); // exit 출력 안되도록 수정해야 함
		break ;
	}
	fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		char	*errno_str = strerror(errno);
		ft_putstr_fd("minishell : ", STD_ERROR);
		ft_putstr_fd(errno_str, STD_ERROR);
		return (1); // errorororor
	}
	write(fd, str, ft_strlen(str));
	close (fd);
	return (0);
}
