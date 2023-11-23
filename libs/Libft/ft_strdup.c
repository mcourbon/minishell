/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:47:03 by momaiouf          #+#    #+#             */
/*   Updated: 2022/11/16 18:43:43 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		lenght;
	char	*duplicata;

	i = 0;
	lenght = ft_strlen(src);
	duplicata = malloc(sizeof(char) * (lenght + 1));
	if (duplicata == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		duplicata[i] = src[i];
		i++;
	}
	duplicata[i] = '\0';
	return (duplicata);
}
