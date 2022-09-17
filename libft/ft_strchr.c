/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:34:19 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/01/15 19:35:35 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (1)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		if (s[i] == '\0')
		{
			if ((unsigned char)c == '\0')
				return ((char *)s + i);
			else
				break ;
		}
		i++;
	}
	return (NULL);
}
