/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:28:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/23 16:48:28 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "msh_tree.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	char	**envp_list;

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
				msh_start_tokenize(str);
			}
			continue ;
		}
		break ;
	}
	exit(0);
}
