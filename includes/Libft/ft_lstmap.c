/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gholloco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:28:45 by gholloco          #+#    #+#             */
/*   Updated: 2024/11/04 03:45:19 by gholloco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, char *(*f)(char *), void (*del)(char *))
{
	t_list	*lst_applied;

	lst_applied = NULL;
	if (!lst || !f || !del)
		return (NULL);
	return (lst_applied);
}
