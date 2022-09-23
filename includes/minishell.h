/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:07:12 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/17 19:10:31 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"

/*
enum e_ttype
{
	T_NULL = 0,
	T_WORD = 1,
	T_REDIR = 2,
	T_PIPE = 3,
	T_DOUBLE_QUOTES = 4,
	T_SINGLE_QUOTES = 5
};

typedef struct s_node{
	enum e_ttype	type;
	char			*str;
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*parent;
}	t_node;

typedef struct s_tree
{
	t_node	*top;
	int		node_count;
}	t_tree;
*/

#endif
