/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 16:25:25 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/01/12 00:01:51 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t l)
{
	size_t	i;
	int		pos;

	i = 0;
	if (src == NULL && dst == NULL)
		return (dst);
	if (dst <= src)
	{
		while (i < l)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		while (i < l)
		{
			pos = l - 1 - i;
			((unsigned char *)dst)[pos] = ((unsigned char *)src)[pos];
			i++;
		}
	}
	return (dst);
}
