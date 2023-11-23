/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:53:34 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/16 18:23:23 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *pointer, int value, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)pointer)[i] = value;
		i++;
	}
	return (pointer);
}
