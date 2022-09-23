/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:11:52 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/01/16 03:07:12 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*testnode;

	if (lst == NULL)
		return (lst);
	testnode = lst;
	while (testnode->next != NULL)
		testnode = testnode->next;
	return (testnode);
}
