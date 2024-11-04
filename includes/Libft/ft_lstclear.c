/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:57:46 by gholloco          #+#    #+#             */
/*   Updated: 2024/02/12 16:58:26 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(char *))
{
	t_list	*node;
	t_list	*temp;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		temp = node;
		node = node->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
