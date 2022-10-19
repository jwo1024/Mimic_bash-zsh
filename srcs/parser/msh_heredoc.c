/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:51:50 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/20 01:29:13 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_parser.h"
#include "builtin.h" 
#include "executor.h"
#include "mini_signal.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>

static int	heredoc_child(char *key, char *file_path);
static char	*heredoc_make_filepath(void);
static int	heredoc_child_write(char *file_path, char *str);

int	msh_heredoc(char *key, t_node *node)
{
	char	*file_path;
	pid_t	pid;
	int		stat_loc;
	int		rtn;

	file_path = heredoc_make_filepath();
	if (file_path == NULL)
		return (msh_print_errno(STD_ERROR, \
					"fail heredoc make_filepath", NULL, 2));
	pid = fork();
	if (pid == 0)
		exit(heredoc_child(key, file_path));
	else if (pid == -1)
	{
		free (file_path);
		return (msh_print_errno(STD_ERROR, "fail heredoc fork", NULL, 2));
	}
	set_signal_fork();
	waitpid(pid, &stat_loc, 0);
	set_signal();
	rtn = msh_exit_status(stat_loc);
	free(node->str2[0]);
	node->str2[0] = file_path;
	return (rtn);
}

static int	heredoc_child(char *key, char *file_path)
{
	char	*str;
	char	*new;
	char	*tmp;

	str = safe_ft_calloc(1, sizeof(char), "heredoc");
	str[0] = '\0';
	set_signal_heredoc();
	while (1)
	{
		new = readline("> ");
		if (new == NULL)
			break ;
		if (ft_strncmp(key, new, ft_strlen(key) + 1) != 0)
		{
			tmp = safe_ft_strjoin(str, new, "heredoc");
			free(str);
			free(new);
			str = safe_ft_strjoin(tmp, "\n", "heredoc");
			continue ;
		}
		free (new);
		break ;
	}
	return (heredoc_child_write(file_path, str));
}

static int	heredoc_child_write(char *file_path, char *str)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return (msh_print_errno(STD_ERROR, "fail heredoc_child", file_path, 1));
	ft_putstr_fd(str, fd);
	close (fd);
	return (0);
}

static char	*heredoc_make_filepath(void)
{
	char		*file_path;
	char		*tmp;
	struct stat	buf;

	tmp = safe_ft_strjoin("/tmp/minishell_heredoc_tmp_", \
					&ft_strrchr(ttyname(STD_OUT), '/')[1], "heredoc");
	file_path = safe_ft_strjoin(tmp, "a", "heredoc");
	free (tmp);
	while (file_path && file_path[ft_strlen(file_path) - 1] <= 'z')
	{
		if (stat(file_path, &buf) == -1)
			break ;
		file_path[ft_strlen(file_path) - 1]++;
	}
	if (errno != 2 || file_path[ft_strlen(file_path) - 1] > 'z')
	{
		free (file_path);
		file_path = NULL;
	}
	return (file_path);
}
