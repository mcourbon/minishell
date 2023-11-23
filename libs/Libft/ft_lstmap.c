/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:21:34 by momaiouf          #+#    #+#             */
/*   Updated: 2023/01/20 16:21:34 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*cpy_list;

	if (lst == NULL)
		return (NULL);
	cpy_list = NULL;
	while (lst != NULL)
	{
		new_list = ft_lstnew((*f)(lst->content));
		if (new_list == NULL)
		{
			ft_lstclear(&cpy_list, del);
			return (NULL);
		}
		ft_lstadd_back(&cpy_list, new_list);
		lst = lst->next;
	}
	return (cpy_list);
}
