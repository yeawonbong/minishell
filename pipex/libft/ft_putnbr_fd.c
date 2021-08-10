/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:26:06 by sma               #+#    #+#             */
/*   Updated: 2021/01/16 23:19:56 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr(long long n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n >= 10)
		putnbr(n / 10, fd);
	ft_putchar_fd((char)((n % 10) + '0'), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	putnbr(n, fd);
}
