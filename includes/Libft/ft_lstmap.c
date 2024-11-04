/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:28:45 by gholloco          #+#    #+#             */
/*   Updated: 2024/02/12 16:59:02 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, char *(*f)(char *), void (*del)(char *))
{
	t_list	*lst_applied;
	//t_list	*node;
	//char	*cont;

	lst_applied = NULL;
	if (!lst || !f || !del)
		return (NULL);
	/*while (lst)
	{
		cont = f(lst->content);
		//node = ft_lstnew(cont);
		if (node == NULL)
		{
			del(cont);
			ft_lstclear(&lst_applied, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_applied, node);
		lst = lst->next;
	}*/
	return (lst_applied);
}
