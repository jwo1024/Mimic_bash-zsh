/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:40:39 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/17 02:08:06 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "mini_signal.h"

void	set_signal(void)
{
	set_terminal_print_off();
	signal(SIGINT, do_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_origin(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_signal_heredoc(void)
{
	signal(SIGINT, do_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	do_sigint_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	exit (1);
}
