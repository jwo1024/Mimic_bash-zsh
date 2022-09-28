/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/28 23:24:52 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	**envp_list;
	t_tree	*tree;

	(void)argc;
	(void)argv;
	envp_list = get_env(envp);
	(void)envp_list;
	set_signal();
	while (1)
	{
		str = readline("minishell $ ");
		if (str != NULL)
		{
			if (str[0] != '\0')
			{
				add_history(str);
				tree = msh_parser(msh_start_tokenize(str));
				msh_tree_print(tree->top);
				msh_executor(tree, envp_list);
				// free tree
			}
			continue ;
		}
		break ;
	}
	exit(0);
}
