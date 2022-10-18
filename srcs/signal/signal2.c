/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:37:36 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 20:09:26 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mini_signal.h"
#include "minishell.h"
#include "libft.h"
#include "tokenizer.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	set_terminal_print_on(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	do_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STD_ERROR);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	change_exit_status(1);
}

void	do_sigterm(void)
{
	ft_putstr_fd("\033[1A", STD_ERROR);
	ft_putstr_fd("\033[12C", STD_ERROR);
	ft_putstr_fd("exit\n", STD_ERROR);
}

void	check_fork_signal(int statloc)
{
	if ((statloc & 255) != 0)
	{
		if ((statloc & 127) == 2)
			ft_putstr_fd("\n", STD_ERROR);
		else if ((statloc & 127) == 3)
			ft_putstr_fd("Quit: 3\n", STD_ERROR);
	}
}
