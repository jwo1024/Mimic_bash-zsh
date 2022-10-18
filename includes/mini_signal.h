/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:33:10 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 20:09:35 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

/*signal*/
void	set_signal(void);
void	set_signal_fork(void);
void	set_signal_origin(void);
void	set_signal_heredoc(void);
void	do_sigint(int signum);
void	do_sigquit(int signum);
void	do_sigterm(void);
void	do_sigint_heredoc(int signum);
void	set_terminal_print_off(void);
void	set_terminal_print_on(void);
void	do_sigint_fork(int signum);
void	check_fork_signal(int statloc);

#endif
