/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/16 21:09:48 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_tree	*tree;

	(void)argc;
	(void)argv;
	g_envp_list = get_env(envp);
	set_signal();
	while (1)
	{
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
					tree = msh_parser(tree);
					change_exit_status(msh_executor(tree));
					if (tree)
						msh_tree_delete(tree);
				}
				fprintf(stderr, "exit status %d\n", ft_atoi(g_envp_list[0]));
			}
			free(str);
			continue ;
		}
		do_sigterm();
		break ;
	}
	exit(ft_atoi(g_envp_list[0]));
}
