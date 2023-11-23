/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:00:05 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/16 18:48:24 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		j;
	int		lenght;

	lenght = ft_strlen(str);
	j = lenght;
	while (j >= 0)
	{
		if (((char)c) == str[j])
			return ((char *) str + j);
		j--;
	}
	if (((char)c) == 0)
		return ((char *) str + j);
	return (0);
}
