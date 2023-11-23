/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:28 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/16 18:50:17 by momaiouf         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (dest[j] != '\0' && j < size)
		j++;
	while (src[i] != '\0' && i + j + 1 < size)
	{
		dest[j + i] = src[i];
		i++;
	}
	if (j != size)
		dest[j + i] = '\0';
	return (ft_strlen(src) + j);
}
