/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 18:44:37 by jaeyjeon          #+#    #+#             */
/*   Updated: 2021/12/20 01:05:55 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countnum(int n)
{
	long	num;
	int		i;

	num = n;
	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		num *= -1;
	}
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		i;

	num = (long)n;
	i = ft_countnum(n) - 1;
	str = (char *)malloc(sizeof(char) * (ft_countnum(n) + 1));
	if (str == 0)
		return (NULL);
	if (n == -2147483648)
		num = 2147483648;
	else if (num < 0)
		num *= -1;
	str[ft_countnum(n)] = '\0';
	while (i >= 0)
	{
		str[i] = (num % 10) + 48;
		num = num / 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
