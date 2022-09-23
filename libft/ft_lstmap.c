/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:57:31 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/01/18 19:04:25 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*savenode;
	t_list	*newlist;
	t_list	*newnode;

	savenode = lst;
	newlist = NULL;
	while (savenode)
	{
		newnode = ft_lstnew(f(savenode->content));
		if (newnode == NULL)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		savenode = savenode->next;
	}
	newnode = NULL;
	return (newlist);
}
