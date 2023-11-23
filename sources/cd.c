/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shifterpro <shifterpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:47:47 by mmaiouf           #+#    #+#             */
/*   Updated: 2023/11/23 14:03:30 by shifterpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// fonction implementant le builtin cd
// on recoit la commande de l'user, par exemple "cd sources", on chope la lenght de la commande
	// et avec substr, on va faire en sorte de choper uniquement le dossier auquel on veut
	// se deplacer, en creeant une nouvelle str commencant par 3 (donc apres cd + ' '), qui aura
	// du coup une length de len - 3 (sams le cd, et choper juste le "sources" par exemple)
// si cd n'a pas d'arguments ou qu'il a seulement un "~", c'est qu'on veut de deplacer dans
	// le repertoire personnelle, alors on remplace sub par la valeur de la variable d'env HOME
// on met ainsi le retour de chdir dans g_error, c'est chdiir() qui va permettre de changer
	// le repertoire de travail, dans un process enfant, avec comme parametre le chemin contenu
	// dans sub
// chdir() retourne -1 si le changement de repertoire echoue (repertoire qui n'existe pas exemple)

void	run_cd(char *temp)
{
	int		len;
	char	*sub;

	len = ft_strlen(temp);
	sub = ft_substr(temp, 3, len - 3);
	if (sub[0] == '\0' || sub[0] == '~')
		sub = ft_strdup(getenv("HOME"));
	g_error = chdir(sub);
	free(sub);
	if (g_error < 0)
		ft_putendl_fd("cd : No such file or directory.", 1);
}
/*
	Après len = ft_strlen(temp)

	Il faut que si il y a des '' ou "", on prenne le dossier normalement
	ex : cd "header" Valide, Mais cd " header" ne marche pas, il faudrait que le dossier s'appelle
		 vraiment " header" avec un espace devant -> entre les quotes c'est vraiment le vrai nom du dossier

	Sans les quotes, il y a autant d'espacement que l'on veut avant et après le cd
	ex : 			cd 					header	      Valide, si le dossier a un espace dans son nom avant les 
		 lettres ça ne marchera jamais il faut les quotes (si le dossier est par ex ' header')
		 
		
	Donc il faudrait une fonction qui détecte si y'a des quotes et enlevé les espaces au début et à la fin
	-> si OUI
				i++ jusqu'à la quote et ensuite temp devient le nom du dossier jusqu'à la dernière
				quote avant le \0
	-> si NON
				i++ en passant le 'cd' aussi jusqu'au prochain caractère qui n'est pas un espacement
				puis prendre le dossier jusqu'à \O
*/