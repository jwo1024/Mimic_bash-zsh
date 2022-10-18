/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/18 18:00:17 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"
#include "mini_signal.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_tree	*tree;
	int		exit_status;


	(void)argc;
	(void)argv;
	g_envp_list = get_env(envp);
	while (1)
	{
		set_signal();
		str = readline("\033[0;36mminishell $ \033[0m");
		if (str != NULL)
		{
			if (check_str_whitespace(str))
				;
			else if (str[0] != '\0')
			{
				add_history(str);
				tree = msh_start_tokenize(str);
				if (tree == NULL)
					change_exit_status(0);
				else
				{
					exit_status = msh_parser(&tree);
					if (exit_status != 0)
						change_exit_status(exit_status);
					else
					{
						change_exit_status(msh_executor(tree));
						if (tree)
							msh_tree_delete(tree);
					}	
				}
			//	system("leaks minishell");
			//	fprintf(stderr, "exit status %d\n", ft_atoi(g_envp_list[0]));
			}
			free(str);
			continue ;
		}
		do_sigterm();
		break ;
	}
	set_terminal_print_on();
	exit(ft_atoi(g_envp_list[0]));
}
