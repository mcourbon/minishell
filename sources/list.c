/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:17:39 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/04 00:31:10 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// en parcourant notre tableau contenant les commandes separees par des pipes, on enleve les espaces
	// inutiles de chaque str
// dans temp2, on cree un nouvel element de la liste, qui va contenir la premiere str (commande)
	// du tableau, une structure qui pointera vers NULL pour l'instant
// puis avec lst_add_back, on l'ajoute a la fin de la liste
// on reinitialise par NULL temp et temp2, avant de tout free a la fin
t_list	**add_list(char **pipe_array, t_list **lst)
{
	int		i;
	char	*temp;
	t_list	*temp2;

	i = 0;
	while (pipe_array[i])
	{
		temp = ft_strtrim(pipe_array[i], " ");
		temp2 = ft_lstnew(temp);
		ft_lstadd_back(lst, temp2);
		temp = NULL;
		temp2 = NULL;
		i++;
	}
	free(temp);
	free(temp2);
	return (lst);
}
