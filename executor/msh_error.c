/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:43:26 by jiwolee           #+#    #+#             */
/*   Updated: 2022/10/03 14:03:36 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	msh_print_errno(char *str)
{
	char	*errno_str;

	errno_str = strerror(errno);
//	fprintf(stderr, "minishell: %s: %s\n", str, strerror(errno), errno);
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, errno_str, ft_strlen(errno_str));
	write(2, "\n", 1);

//	free(errno_str);
}
