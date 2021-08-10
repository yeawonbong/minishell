/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 16:05:38 by sma               #+#    #+#             */
/*   Updated: 2021/01/11 02:07:01 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	i = 0;
	if (lst)
	{
		ptr = lst;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
			i++;
		}
		if (ptr->next == NULL)
			i++;
	}
	return (i);
}
