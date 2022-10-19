/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 02:35:01 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/19 16:16:19 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "libft.h"

char	*free_ret(char *env_name, char *str)
{
	free(env_name);
	if (str == NULL)
		return (NULL);
	return (safe_ft_strdup(str, "get_env"));
}

int	check_double_flag(char *s, int double_flag)
{
	if (double_flag == 1)
		double_flag = 0;
	else if (skip_dquot(s) != 0 && double_flag == 0)
		double_flag = 1;
	return (double_flag);
}
