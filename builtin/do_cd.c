/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:47 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/07 16:43:29 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_cd(char *s, int fd)
{
	char	*dir;
	char	*save_dir;
	char	*old_pwd;

	if (s[3] == '\0')
		return (chdir(getenv("HOME")));
	dir = ft_strdup(&s[3]);
	if (dir[0] == '~' && (dir[1] == '\0' || dir[1] == '/'))
	{
		save_dir = ft_strjoin(getenv("HOME"), &dir[1]);
		free(dir);
		dir = save_dir;
	}
	old_pwd = getcwd(NULL, 1024);
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishell: cd: ", fd); // 임시
		ft_putstr_fd(dir, fd);
		ft_putstr_fd(": No such file or directory", fd);
		ft_putstr_fd("\n", fd);
		free(old_pwd);
		free(dir);
		return (1);
	}
	else
		change_pwd(old_pwd);
	free (dir);
	return (0);
}

void	change_pwd(char *old_pwd)
{
	char	*pwd;
	char	*pwd2;

	pwd = ft_strjoin("OLDPWD=", old_pwd);
	change_env(pwd);
	free(old_pwd);
	old_pwd = getcwd(NULL, 1024);
	pwd2 = ft_strjoin("PWD=", old_pwd);
	change_env(pwd2);
	free(old_pwd);
}
