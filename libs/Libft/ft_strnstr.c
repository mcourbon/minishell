/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:52:11 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/16 18:42:17 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (tofind[0] == '\0')
		return ((char *)(str));
	while (i < len && str[i])
	{
		j = 0;
		while (str[i + j] == tofind[j])
		{
			if (i + j >= len)
				return (NULL);
			if (tofind[j + 1] == '\0')
				return (&((char *)str)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
