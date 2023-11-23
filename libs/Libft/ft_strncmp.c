/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:19:05 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/17 12:32:18 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				equal;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	equal = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((i < n) && (str1[i] != '\0' || str2[i] != '\0'))
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str2[i] > str1[i])
			return (-1);
		i++;
	}
	return (equal);
}
