/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:51:50 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/17 17:01:55 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"
#include	"mini_signal.h"

int	msh_heredoc(char *key, t_node *node)
{
	char	*file_path;
	pid_t	pid;
	int		stat_loc;
	int		rtn;

	file_path = ft_strjoin("/tmp/minishell_heredoc_tmp_", key); // heredoc용 파일 경로 만들기
	if (file_path == NULL)
		exit(msh_print_errno(STD_ERROR, "fail heredoc get file_path", NULL, 1));
	pid = fork(); // fork()
	if (pid == 0)//자식프로세스
		exit(msh_heredoc_child(key, file_path));
	else if (pid == -1) // fork 오류시
	{
		msh_print_errno(STD_ERROR, "fail heredoc fork", NULL, 1);
		free (file_path);
		return (-1);
	}
	set_signal_fork(); // heredoc이 실행되는동안 signal 출력하지않도록 변경
	waitpid(pid, &stat_loc, 0);// wait()
	set_signal(); // 다시 시그널 출력하도록 변경
	rtn = msh_exit_status(stat_loc); // exit_status 받아옴
	fprintf(stderr, "heredoc exit %d\n", rtn);
	// 현재 rtn 된 값은 parser를 통해서 반환되어야 하는데
	// 구조가 그렇지 못해서 적용은 안되고 fprintf로 확인중입니다.

	if (rtn != 0) // 오류 종료시
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

	str = ft_calloc(1, sizeof(char));
	str[0] = '\0';
	set_signal_heredoc(); // heredoc전용 SIGINT를 수행할 signal
	while (1)
	{
		new = readline("> ");
		if (new == NULL)
			exit (0);
		if (ft_strncmp(key, new, ft_strlen(key) + 1) != 0) // key 값이랑 같지 않을 때 입력을 받음
		{
			// 기존 str + 입력받은 str + '\n'
			tmp = ft_strjoin(str, new);
			if (tmp == NULL)
				exit (msh_print_errno(STD_ERROR, "fail heredoc_child", NULL, 1));
			free(str);
			free(new);
			str = ft_strjoin(tmp, "\n");
			if (str == NULL)
				exit (msh_print_errno(STD_ERROR, "fail heredoc_child", NULL, 1));
			continue ;
		}
		// new 가 key 값과 일치할때 break;
		free (new);
		break ;
	}
	return (msh_heredoc_child_write(file_path, str));
}

int	msh_heredoc_child_write(char *file_path, char *str)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (msh_print_errno(STD_ERROR, "<<", NULL, 1));
	write(fd, str, ft_strlen(str));
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
