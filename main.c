/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/03 13:23:13 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_list	*envp_list;
	t_tree	*tree;
	int		exit_status;

	(void)argc;
	(void)argv;
	envp_list = get_env(envp);
	(void)envp_list;
	set_signal();
	while (1)
	{
		str = readline("\033[0;36mminishell $ \033[0m");
		if (str != NULL)
		{
			if (str[0] != '\0')
			{
				add_history(str);
				tree = msh_parser(msh_start_tokenize(str));
				if (tree == NULL)
				{
					exit_status = 258; // 130? 
					/*
					Bash uses the value 128+*N*  as the exit status.
					fatal signal N → 128 + N
					command is not found → 127
					command is found but is not executable → 126
					*/
				}
				exit_status = msh_executor(tree, envp); // envp_list 대신 임시
				fprintf(stderr, "exit status %d\n", exit_status);
				msh_tree_delete(tree);
			}
			continue ;
		}
		do_sigterm();
		break ;
	}
	exit(0);
}
