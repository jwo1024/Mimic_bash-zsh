/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:47 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/16 20:41:20 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

int	do_cd(char **s, int *fd)
{
	char	*dir;
	char	*save_dir;
	char	*old_pwd;

	if (s[1] == NULL || s[1][0] == '\0')
	{
		old_pwd = getcwd(NULL, 0);
		if (old_pwd == NULL)
			return (msh_print_errno(fd[STD_ERROR], "pwd", NULL, 1));
		if (chdir(getenv("HOME")) != 0)
			return (print_cd_error(ft_strdup(getenv("HOME")), old_pwd, fd));
		change_pwd(old_pwd);
		return (0);
	}
	dir = safe_ft_strdup(s[1], "cd");
	if (dir[0] == '~' && (dir[1] == '\0' || dir[1] == '/'))
	{
		save_dir = safe_ft_strjoin(getenv("HOME"), &dir[1], "cd");
		free(dir);
		dir = save_dir;
	}
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
	{
		free(dir);
		return (msh_print_errno(fd[STD_ERROR], "pwd", NULL, 1));
	}
	if (chdir(dir) != 0)
		return (print_cd_error(dir, old_pwd, fd));
	else
		change_pwd(old_pwd);
	free (dir);
	return (0);
}

void	change_pwd(char *old_pwd)
{
	char	*pwd;
	char	*pwd2;

	pwd = safe_ft_strjoin("OLDPWD=", old_pwd, "cd");
	g_envp_list = change_env(pwd);
	free(old_pwd);
	old_pwd = getcwd(NULL, 0);
	pwd2 = safe_ft_strjoin("PWD=", old_pwd, "cd");
	g_envp_list = change_env(pwd2);
	free(old_pwd);
}

int	print_cd_error(char *dir, char *old_pwd, int *fd)
{
	msh_print_errno(fd[STD_ERROR], "cd", dir, 0);
	free(old_pwd);
	free(dir);
	return (1);
}
