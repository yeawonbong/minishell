/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:31:13 by sma               #+#    #+#             */
/*   Updated: 2021/01/01 01:37:10 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_transf(long long n, char *str, int len)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		while (len >= 1)
		{
			str[len] = '0' + n % 10;
			n = n / 10;
			len--;
		}
	}
	else
	{
		while (len >= 0)
		{
			str[len] = '0' + n % 10;
			n = n / 10;
			len--;
		}
	}
	return (str);
}

int				ft_strlen2(long long n)
{
	int			len;
	long long	a;

	a = n;
	len = 0;
	if (a <= 0)
	{
		len++;
		a *= -1;
	}
	while (a > 0)
	{
		a = a / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int			len;
	char		*str;

	len = ft_strlen2(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	return (ft_transf(n, str, len));
}
