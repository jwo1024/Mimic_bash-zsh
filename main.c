/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/12 23:55:33 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_tree	*tree;
	int		exit_status;

	(void)argc;
	(void)argv;
	g_envp_list = get_env(envp);
	set_signal();
	exit_status = 0;
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
					continue ;
				exit_status = msh_executor(tree);
				msh_tree_delete(tree);
				fprintf(stderr, "exit status %d\n", exit_status);
			}
			continue ;
		}
		do_sigterm();
		break ;
	}
	exit(0);
}
