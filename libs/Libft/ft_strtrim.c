/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:42:42 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/18 16:56:08 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len_s1;
	char	*mystr;

	i = 0;
	len_s1 = ft_strlen(s1) - 1;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] && is_in_set(set, s1[i]))
		i++;
	while (len_s1 > i && is_in_set(set, s1[len_s1]))
		len_s1--;
	mystr = (char *)malloc(sizeof(char) * ((len_s1 - i) + 2));
	if (mystr == NULL)
		return (NULL);
	ft_memcpy(mystr, s1 + i, (len_s1 - i) + 1);
	mystr[len_s1 - i + 1] = '\0';
	return (mystr);
}
