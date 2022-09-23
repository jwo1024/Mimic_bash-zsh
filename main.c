/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/23 19:34:10 by jaeyjeon         ###   ########.fr       */
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
		str = readline("\033[0;36mminishell $ \033[0m");
		if (str != NULL)
		{
			if (str[0] != '\0')
			{
				add_history(str);
				tree = msh_parser(msh_start_tokenize(str));
				msh_tree_print(tree->top);
			}
			continue ;
		}
		do_sigterm();
		break ;
	}
	exit(0);
}
