/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momaiouf <momaiouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:56:26 by momaiouf          #+#    #+#             */
/*   Updated: 2022/12/05 15:56:26 by momaiouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_word(char const *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_malloc_case(char const	*str, char c)
{
	int		i;
	int		len;
	char	*mycase;

	i = 0;
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	mycase = (char *)malloc(sizeof(char) * len + 1);
	if (mycase == NULL)
		return (NULL);
	while (str[i] && str[i] != c)
	{
		mycase[i] = str[i];
		i++;
	}
	mycase[i] = '\0';
	return (mycase);
}

static char	**ft_freeall(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**mystr;

	if (s == NULL)
		return (NULL);
	i = 0;
	mystr = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (mystr == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			mystr[i] = ft_malloc_case(s, c);
			i++;
			if (mystr[i - 1] == NULL)
				return (ft_freeall(mystr));
			while (*s && *s != c)
				s++;
		}
	}
	mystr[i] = 0;
	return (mystr);
}
