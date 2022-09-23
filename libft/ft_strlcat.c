/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:21:25 by jaeyjeon          #+#    #+#             */
/*   Updated: 2021/12/10 02:03:25 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	left;
	size_t	dstlen;
	size_t	srclen;

	left = size;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size <= ft_strlen(dst))
		return (size + srclen);
	while (*dst != '\0' && left != 0)
	{
		dst++;
		left--;
	}
	while (left != 1 && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		left--;
	}
	*dst = '\0';
	return (srclen + dstlen);
}
