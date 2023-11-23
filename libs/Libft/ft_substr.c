/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:44:48 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/18 18:45:20 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		i;
	size_t		len_str;

	i = -1;
	len_str = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= len_str)
		substr = (char *)malloc(sizeof(char));
	else if (len >= len_str)
		substr = (char *)malloc(sizeof(char) * (len_str - start) + 1);
	else if ((start + len) > len_str)
		substr = (char *)malloc(sizeof(char) * (len));
	else
		substr = (char *)malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (++i < len && start < len_str)
	{
		substr[i] = s[start];
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
