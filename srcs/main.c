/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/19 16:37:55 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msh_tree.h"
#include "tokenizer.h"
#include "executor.h"
#include "mini_signal.h"
#include "msh_parser.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;

	(void)argc;
	(void)argv;
	g_envp_list = get_env(envp);
	while (1)
	{
		set_signal();
		str = readline("minishell $ ");
		if (str != NULL)
		{
			run_minishell(str);
			free(str);
			continue ;
		}
		do_sigterm();
		break ;
	}
	set_terminal_print_on();
	exit(ft_atoi(g_envp_list[0]));
}

void	run_minishell(char *str)
{
	t_tree	*tree;
	int		exit_status;

	if (check_str_whitespace(str))
		;
	else if (str[0] != '\0')
	{
		add_history(str);
		tree = msh_start_tokenize(str);
		if (tree == NULL)
			exit_status = 0;
		else
		{
			exit_status = msh_parser(&tree);
			if (exit_status == 0)
				exit_status = msh_executor(tree);
		}
		if (tree)
			msh_tree_delete(tree);
		change_exit_status(exit_status);
	}
}
