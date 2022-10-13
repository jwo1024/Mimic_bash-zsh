/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:57:18 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/13 20:32:48 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "msh_tree.h"
# include "builtin.h"

t_tree	*msh_start_tokenize(char *s, int exit_status);
void	change_whitespace(char *s);
char	*change_each_oper(char *s, char op);
char	*change_redir(char *s, char op);
char	*change_oper(char *s);
int		is_whitespace(char c);
int		skip_dquot(char *s);
int		count_new_space(char *s, char c);
t_node	*split_str(char *str);
t_node	*make_new(char *str, int size);
void	add_next(t_node *new, t_node *start);
void	do_change_redir(char *str, char *s, t_index *idx, char op);
void	do_change_each_oper(char *str, char *s, t_index *idx, char op);
char	*get_env_to_str(char *env_name, int exit_status);
char	*get_env_at_tokenizer(char *s, int exit_status);
char	*del_dequot(char **s);
void	do_del_dequot(char *new_str, char *s, char c, t_index *idx);
char	*get_env_name(char *s);
int		get_env_name_size(char *s);
char	*get_merged_env_str(char *s, char *env);
char	*ft_strjoin_check_null(char *s1, char *s2);

#endif
