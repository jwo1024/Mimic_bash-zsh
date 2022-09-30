/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:47 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/29 15:49:38 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	do_cd(char *s, int fd)
{
	char	*dir;
	char	*save_dir;

	(void)fd;
	if (s[3] == '\0')
		return (chdir(getenv("HOME")));
	dir = ft_strdup(&s[3]);
	if (dir[0] == '~' && (dir[1] == '\0' || dir[1] == '/'))
	{
		save_dir = ft_strjoin(getenv("HOME"), &dir[1]);
		free(dir);
		dir = save_dir;
	}
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", fd); // 임시
		ft_putstr_fd(dir, fd);
		ft_putstr_fd("\n", fd);
	}
	free (dir);
	return (1);
}
