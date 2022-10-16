/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:40:39 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/17 01:13:49 by jaeyjeon         ###   ########.fr       */
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

void	do_signal_heredoc(void)
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

void	do_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	change_exit_status(1);
}

void	do_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 1);
}

void	do_sigterm(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd("\033[12C", 1);
	ft_putstr_fd("exit\n", 1);
}
