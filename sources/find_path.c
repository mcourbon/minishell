/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaiouf <mmaiouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:10:48 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/03 23:11:42 by mmaiouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// - fonction qui va parcourir le tableau qui contient les repertoires repertoriees dans la 
	// variable d'env PATH.
// - pour chaque repertoire : on copie sa valeur, on lui ajoute a la fin un slash pour accueillir
	// la commande et la coller au chemin, avec les deux strjoin.
// - apres avoir free le strdup et qu'on a notre chemin, on check si l'exe existe 
	// dans la variable PATH, pour chaque chemin du tableau
// - si c'est le cas, on assigne a current_path notre path exacte, on free les strjoin et on
	// la retourne

char	*check_path(char *command, int i)
{
	char	**array;
	char	*path;
	char	*current_path;
	char	*temp;

	array = ft_split(getenv("PATH"), ':');
	while (array[++i])
	{
		temp = ft_strdup(array[i]);
		array[i] = ft_strjoin(temp, "/");
		path = ft_strjoin(array[i], command);
		if (temp[0] != '\0')
			free(temp);
		if (access(path, F_OK) == 0)
		{
			current_path = ft_strdup(path);
			free(path);
			ft_free_str(array);
			return (current_path);
		}
		free(path);
	}
	ft_free_str(array);
	return (NULL);
}


// - fonction principale pour obtenir le chemin d'acces complet d'une commande
// - avec la commande access, on verifie si la commande est un commande absolue, par exemple
	// "bin/ls", avec la macro F_OK, pour savoir si l'executable de ce chemin existe dans 
	// le systeme de fichiers. si c'est le cas, on renvoie direct la path a run_child pour
	// qu'il execute la commande avec execve
// - si c'est pas le cas, on appelle check_path our rechercher la commande dans les 
	// repertoires du PATH (avec -1 pour i car plus de place lol)
char	*find_path(char *command)
{
	char	*path;

	path = NULL;
	if (access(command, F_OK) == 0) 
		return (command);
	path = check_path(command, -1); 
	if (path != NULL)
		return (path);
	if (path[0] != '\0')
		return (path);
	return (NULL);
}
