/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 17:43:19 by jaeyjeon          #+#    #+#             */
/*   Updated: 2021/12/24 18:41:11 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nlist;

	nlist = (t_list *)malloc(sizeof(t_list));
	if (nlist == 0)
		return (NULL);
	nlist->content = content;
	nlist->next = NULL;
	return (nlist);
}
