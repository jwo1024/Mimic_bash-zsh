/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwolee <jiwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:49:11 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/10/15 16:24:51 by jiwolee          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}	t_index;

t_index	*make_idx(void);
/*builtin*/
int		do_pwd(int *fd);
int		check_word(char *word);
int		do_echo(char **word, int *fd);
int		do_env(int *fd);
int		do_cd(char **s, int *fd);
int		print_cd_error(char *dir, char *old_pwd, int *fd);
int		check_opt(char **s);
int		check_dequot(char *s);
int		find_equal(char *word);
int		do_export(char **word, int *fd);
char	**change_env_at_export(char *str, char **new_list, int i);
char	**change_env(char *str);
int		check_export_word(char *word, int *fd);
int		check_dup(char *str, char *env_list);
int		error_print_export(char *str, char *word, int *fd);
void	change_pwd(char *old_pwd);
void	free_env(char **env);
char	**malloc_env(int size);
void	print_env(int *fd);
void	print_env_print_part(char *str, int *fd);
char	**sort_env(void);
int		do_unset(char **word, int *fd);
void	unset_env(t_index *idx);
int		check_unset_dup(char *str, char *env);
int		do_exit(char **word, int *fd);
void	print_errmsg_at_exit(int *fd, char *copy_str);
int		get_envp_size(void);
int		check_next_dol(char c);

#endif
