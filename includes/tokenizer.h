/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:57:18 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/23 16:57:23 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "msh_tree.h"

t_node	*msh_start_tokenize(char *s);
void	change_whitespace(char *s);
char	*change_each_oper(char *s, char op);
char	*change_redir(char *s, char op);
char	*change_oper(char *s);
int		is_whitespace(char c);
int		skip_dquot(char *s);
int		count_dquot(char *s);
int		count_new_space(char *s, char c);
t_node	*split_str(char *str);
t_node	*make_new(char *str, int size);
void	add_next(t_node *new, t_node *start);

#endif
