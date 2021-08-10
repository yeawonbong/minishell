/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:20:50 by sma               #+#    #+#             */
/*   Updated: 2021/06/19 17:38:55 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_isspace(const char *c)
{
	int				i;

	i = 0;
	while (c[i] == '\t' || c[i] == '\v' || c[i] == '\f' \
			|| c[i] == '\r' || c[i] == '\n' || c[i] == ' ')
		i++;
	return (i);
}

int					ft_atoi(const char *c)
{
	int				i;
	long long		num;
	int				sign;

	i = ft_isspace(c);
	num = 0;
	sign = 1;
	if (c[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (c[i] == '+')
		i++;
	while ('0' <= c[i] && c[i] <= '9')
	{
		num = num * 10 + (c[i] - '0');
		if (2147483647 < num * sign)
			return (-1);
		else if (num * sign < -2147483648)
			return (0);
		i++;
	}
	return ((num * sign));
}
