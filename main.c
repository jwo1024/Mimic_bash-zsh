/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/05 23:08:41 by jiwolee          ###   ########seoul.kr  */
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
	set_signal();
	while (1)
	{
		str = readline("\033[0;36mminishell $ \033[0m");
		if (str != NULL)
		{
			if (str[0] != '\0')
			{
				envp_list = do_export("export QQ0ASD=12334 _BBV=300 0QQASD=9393 IU=4242 asd=123bcd=123", envp_list, 1);
				do_env(envp_list, 1);
				add_history(str);
				tree = msh_parser(msh_start_tokenize(str));
				msh_executor(tree, envp_list);
				msh_tree_delete(tree);
			}
			continue ;
		}
		do_sigterm();
		break ;
	}
	exit(0);
}
