/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:20:52 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 01:21:23 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// compter le nombre d'un caractere specifique dans une str
int	count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

// permet de transformer un tableau de chaines de caracteres contenant la commande 
char	*sub_redir(char **str, int i)
{
	char	*temp;
	int		j;
	int		k;
	int		m;

	j = 0;
	k = 0;
	temp = malloc(sizeof(char) * 100);
	if (temp == NULL)
		return (NULL);
	while (k < i)
	{
		m = 0;
		while (str[k][m])
			temp[j++] = str[k][m++];
		temp[j] = ' ';
		j++;
		k++;
	}
	temp[j - 1] = '\0';
	return (temp);
}
