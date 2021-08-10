/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sma <sma@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 00:53:17 by sma               #+#    #+#             */
/*   Updated: 2021/01/11 01:46:28 by sma              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*ptr;

	if (!(ptr = (t_list*)malloc(sizeof(t_list))))
		return (0);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
