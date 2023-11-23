/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:15:42 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/17 15:36:11 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	if (dest == NULL && src == NULL)
		return (NULL);
	if ((unsigned char *)dest < (unsigned const char *)src)
		return (ft_memcpy(dest, src, size));
	while (size--)
	{
		((unsigned char *)dest)[size] = ((unsigned const char *)src)[size];
	}
	return (dest);
}
