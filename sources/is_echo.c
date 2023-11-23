/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:16:17 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:17:31 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// fonction pour compter le nombre de caracteres, sans compter les guillemets, pour le malloc
int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			count++;
		i++;
	}
	return (i - count);
}

// fonction qui cree une nouvelle str, qui va contenir la commande de l'user, sans les quotes
char	*remove_quotes(char *str, int i)
{
	char	*temp;
	int		j;

	j = 0;
	temp = malloc(sizeof(char) * (count_quotes(str) + 1));
	if (temp == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
			temp[j++] = str[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

// fonction qui determine si la commande commence bien par echo, tout en ignorant les espaces
	// au debut, et obtenir la version de la commande sans guillemets
int	is_echo(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] == ' ')
		i++;
	temp = remove_quotes(str, i);
	i = 0;
	if (!ft_strncmp(temp, "echo", 4))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
