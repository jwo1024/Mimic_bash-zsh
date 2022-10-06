/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:49:11 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/06 21:11:57 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

t_index	*make_idx(void);
/*builtin*/
int		do_pwd(int fd);
int		check_word(char *word);
int		do_exit(char *word);
int		do_echo(char *word, int fd);
int		do_env(char **env_list, int fd);
int		do_cd(char *s, int fd);
int		check_opt(char *s);
int		check_dequot(char *s);
int		find_equal(char *word);
char	*del_dequot(char *s);
void	do_del_dequot(char *new_str, char *s, char c, t_index *idx);
char	**do_export(char *word, int fd);
char	**change_env(char *str, char **env_list);
int		check_export_word(char *word, int fd);
int		check_dup(char *str, char *env_list);
int		error_print_export(char *str, char *word, int fd, int i);

#endif
