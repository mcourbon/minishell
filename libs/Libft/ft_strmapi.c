/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:56:51 by momaiouf          #+#    #+#             */
/*   Updated: 2022/12/05 15:56:51 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*mystr;
	int		len;

	if (s == NULL || f == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	mystr = malloc(sizeof(char) * (len + 1));
	if (mystr == NULL)
		return (NULL);
	while (s[i])
	{
		mystr[i] = (*f)(i, s[i]);
		i++;
	}
	mystr[i] = '\0';
	return (mystr);
}
