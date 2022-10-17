/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:51:50 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/18 02:50:28 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	"mini_signal.h"

char	*msh_heredoc_make_filepath(void);

int	msh_heredoc(char *key, t_node *node)
{
	char	*file_path;
	pid_t	pid;
	int		stat_loc;
	int		rtn;

	file_path = msh_heredoc_make_filepath();
	if (file_path == NULL)
		exit(msh_print_errno(STD_ERROR, "fail heredoc get file_path", NULL, 1));
	pid = fork();
	if (pid == 0)
		exit(msh_heredoc_child(key, file_path));
	else if (pid == -1)
	{
		msh_print_errno(STD_ERROR, "fail heredoc fork", NULL, 1);
		free (file_path);
		return (-1);
	}
	set_signal_fork(); // heredoc이 실행되는동안 signal 출력하지않도록 변경
	waitpid(pid, &stat_loc, 0);
	set_signal(); // 다시 시그널 출력하도록 변경
	rtn = msh_exit_status(stat_loc);
	free(node->str2[0]);
	node->str2[0] = file_path;
	fprintf(stderr, "rtn %d\n", rtn);
	return (rtn);
}

int	msh_heredoc_child(char *key, char *file_path)
{
	char	*str;
	char	*new;
	char	*tmp;

	str = ft_calloc(1, sizeof(char));
	str[0] = '\0';
	set_signal_heredoc(); // heredoc전용 SIGINT를 수행할 signal
	while (1)
	{
		new = readline("> ");
		if (new == NULL)
			break ;
		if (ft_strncmp(key, new, ft_strlen(key) + 1) != 0)
		{
			tmp = ft_strjoin(str, new);
			if (tmp == NULL)
				exit (msh_print_errno(STD_ERROR, "fail heredoc", NULL, 1));
			free(str);
			free(new);
			str = ft_strjoin(tmp, "\n");
			if (str == NULL)
				exit (msh_print_errno(STD_ERROR, "fail heredoc", NULL, 1));
			continue ;
		}
		free (new);
		break ;
	}
	return (msh_heredoc_child_write(file_path, str));
}

int	msh_heredoc_child_write(char *file_path, char *str)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return (msh_print_errno(STD_ERROR, "fail heredoc", file_path, 1));
	if (write(fd, str, ft_strlen(str)) == -1)
		return (msh_print_errno(STD_ERROR, "fail heredoc", file_path, 1));
	close (fd);
	return (0);
}

/* // norm 맞추기 위해 나중에 나눌 함수입니다. 지우지 말아주세요!
char *msh_heredoc_child_read(char *key, char *new)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(str, new);
	if (tmp == NULL)
		exit (msh_print_errno(STD_ERROR, "fail heredoc_child", NULL, 1));
	free(str);
	free(new);
	str = ft_strjoin(tmp, "\n");
	if (str == NULL)
		exit (msh_print_errno(STD_ERROR, "fail heredoc_child", NULL, 1));
	return (str);
}
*/

char	*msh_heredoc_make_filepath(void)
{
	char		*file_path;
	char		*tmp;
	struct stat buf;

	file_path = ttyname(STD_OUT);
	file_path = ft_strrchr(file_path, '/');
	tmp = ft_strjoin("/tmp/minishell_heredoc_tmp_", &file_path[1]);
	if (tmp == NULL)
		exit (msh_print_errno(STD_ERROR, "fail heredoc", NULL, 1));
	file_path = tmp;
	tmp = ft_strjoin(file_path, "a");
	if (tmp == NULL)
		exit (msh_print_errno(STD_ERROR, "fail heredoc", NULL, 1));	
	free (file_path);
	file_path = tmp;

	fprintf(stderr, "%s\n%c\n", file_path, file_path[ft_strlen(file_path) -1]);

	while (file_path[ft_strlen(file_path) - 1] <= 'z')
	{
		if (lstat(file_path, &buf) == -1)
		{
			if (errno != 2)
				free(file_path);
			break ;
		}
		else if (file_path[ft_strlen(file_path) - 1] == 'z')
		{
			free (file_path);
			break ;
		}
		//	return (free(file_path));
		file_path[ft_strlen(file_path) - 1]++;
	}

	fprintf(stderr, "%s\n%c\n", file_path, file_path[ft_strlen(file_path)]);
	return (file_path);
}
