/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:52:32 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/27 21:00:04 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

t_index	*make_idx(void)
{
	t_index	*new;

	new = malloc(sizeof(t_index));
	new->i = 0;
	new->j = 0;
	return (new);
}
